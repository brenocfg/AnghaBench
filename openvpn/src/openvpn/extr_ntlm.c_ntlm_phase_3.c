#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  userdomain ;
typedef  int uint8_t ;
struct TYPE_2__ {char* username; char* password; } ;
struct http_proxy_info {scalar_t__ auth_method; TYPE_1__ up; } ;
struct gc_arena {int dummy; } ;
typedef  int /*<<< orphan*/  phase3 ;
typedef  int /*<<< orphan*/  domain ;
typedef  int /*<<< orphan*/  buf2 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CLEAR (int*) ; 
 int DES_KEY_LENGTH ; 
 scalar_t__ HTTP_AUTH_NTLM2 ; 
 int MD4_DIGEST_LENGTH ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  add_security_buffer (int,...) ; 
 int /*<<< orphan*/  cipher_des_encrypt_ecb (unsigned char*,int*,int*) ; 
 int /*<<< orphan*/  create_des_keys (int*,unsigned char*) ; 
 int /*<<< orphan*/  gen_hmac_md5 (int*,int,int*,int,int*) ; 
 int /*<<< orphan*/  gen_md4_hash (int*,int,int*) ; 
 int /*<<< orphan*/  gen_nonce (int*) ; 
 int /*<<< orphan*/  gen_timestamp (int*) ; 
 scalar_t__ make_base64_string2 (unsigned char*,int,struct gc_arena*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  my_strupr (char*) ; 
 int openvpn_base64_decode (char const*,int*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int unicodize (char*,char*) ; 

const char *
ntlm_phase_3(const struct http_proxy_info *p, const char *phase_2,
             struct gc_arena *gc)
{
    /* NTLM handshake
     *
     * http://davenport.sourceforge.net/ntlm.html
     *
     */

    char pwbuf[sizeof(p->up.password) * 2]; /* for unicode password */
    uint8_t buf2[128]; /* decoded reply from proxy */
    uint8_t phase3[464];

    uint8_t md4_hash[MD4_DIGEST_LENGTH + 5];
    uint8_t challenge[8], ntlm_response[24];
    int i, ret_val;

    uint8_t ntlmv2_response[144];
    char userdomain_u[256];     /* for uppercase unicode username and domain */
    char userdomain[128];       /* the same as previous but ascii */
    uint8_t ntlmv2_hash[MD5_DIGEST_LENGTH];
    uint8_t ntlmv2_hmacmd5[16];
    uint8_t *ntlmv2_blob = ntlmv2_response + 16;     /* inside ntlmv2_response, length: 128 */
    int ntlmv2_blob_size = 0;
    int phase3_bufpos = 0x40;     /* offset to next security buffer data to be added */
    size_t len;

    char domain[128];
    char username[128];
    char *separator;

    bool ntlmv2_enabled = (p->auth_method == HTTP_AUTH_NTLM2);

    CLEAR(buf2);

    ASSERT(strlen(p->up.username) > 0);
    ASSERT(strlen(p->up.password) > 0);

    /* username parsing */
    separator = strchr(p->up.username, '\\');
    if (separator == NULL)
    {
        strncpy(username, p->up.username, sizeof(username)-1);
        username[sizeof(username)-1] = 0;
        domain[0] = 0;
    }
    else
    {
        strncpy(username, separator+1, sizeof(username)-1);
        username[sizeof(username)-1] = 0;
        len = separator - p->up.username;
        if (len > sizeof(domain) - 1)
        {
            len = sizeof(domain) - 1;
        }
        strncpy(domain, p->up.username,  len);
        domain[len] = 0;
    }


    /* fill 1st 16 bytes with md4 hash, disregard terminating null */
    int unicode_len = unicodize(pwbuf, p->up.password) - 2;
    gen_md4_hash((uint8_t *)pwbuf, unicode_len, md4_hash);

    /* pad to 21 bytes */
    memset(md4_hash + MD4_DIGEST_LENGTH, 0, 5);

    ret_val = openvpn_base64_decode(phase_2, buf2, -1);
    if (ret_val < 0)
    {
        return NULL;
    }

    /* we can be sure that phase_2 is less than 128
     * therefore buf2 needs to be (3/4 * 128) */

    /* extract the challenge from bytes 24-31 */
    for (i = 0; i<8; i++)
    {
        challenge[i] = buf2[i+24];
    }

    if (ntlmv2_enabled)      /* Generate NTLMv2 response */
    {
        int tib_len;

        /* NTLMv2 hash */
        strcpy(userdomain, username);
        my_strupr(userdomain);
        if (strlen(username) + strlen(domain) < sizeof(userdomain))
        {
            strcat(userdomain, domain);
        }
        else
        {
            msg(M_INFO, "Warning: Username or domain too long");
        }
        unicodize(userdomain_u, userdomain);
        gen_hmac_md5((uint8_t *)userdomain_u, 2 * strlen(userdomain), md4_hash,
                     MD5_DIGEST_LENGTH, ntlmv2_hash);

        /* NTLMv2 Blob */
        memset(ntlmv2_blob, 0, 128);                        /* Clear blob buffer */
        ntlmv2_blob[0x00] = 1;                              /* Signature */
        ntlmv2_blob[0x01] = 1;                              /* Signature */
        ntlmv2_blob[0x04] = 0;                              /* Reserved */
        gen_timestamp(&ntlmv2_blob[0x08]);                  /* 64-bit Timestamp */
        gen_nonce(&ntlmv2_blob[0x10]);                      /* 64-bit Client Nonce */
        ntlmv2_blob[0x18] = 0;                              /* Unknown, zero should work */

        /* Add target information block to the blob */

        /* Check for Target Information block */
        /* The NTLM spec instructs to interpret these 4 consecutive bytes as a
         * 32bit long integer. However, no endianness is specified.
         * The code here and that found in other NTLM implementations point
         * towards the assumption that the byte order on the wire has to
         * match the order on the sending and receiving hosts. Probably NTLM has
         * been thought to be always running on x86_64/i386 machine thus
         * implying Little-Endian everywhere.
         *
         * This said, in case of future changes, we should keep in mind that the
         * byte order on the wire for the NTLM header is LE.
         */
        const size_t hoff = 0x14;
        unsigned long flags = buf2[hoff] | (buf2[hoff + 1] << 8)
                              |(buf2[hoff + 2] << 16) | (buf2[hoff + 3] << 24);
        if ((flags & 0x00800000) == 0x00800000)
        {
            tib_len = buf2[0x28];            /* Get Target Information block size */
            if (tib_len > 96)
            {
                tib_len = 96;
            }

            {
                uint8_t *tib_ptr;
                uint8_t tib_pos = buf2[0x2c];
                if (tib_pos + tib_len > sizeof(buf2))
                {
                    return NULL;
                }
                /* Get Target Information block pointer */
                tib_ptr = buf2 + tib_pos;
                /* Copy Target Information block into the blob */
                memcpy(&ntlmv2_blob[0x1c], tib_ptr, tib_len);
            }
        }
        else
        {
            tib_len = 0;
        }

        /* Unknown, zero works */
        ntlmv2_blob[0x1c + tib_len] = 0;

        /* Get blob length */
        ntlmv2_blob_size = 0x20 + tib_len;

        /* Add challenge from message 2 */
        memcpy(&ntlmv2_response[8], challenge, 8);

        /* hmac-md5 */
        gen_hmac_md5(&ntlmv2_response[8], ntlmv2_blob_size + 8, ntlmv2_hash,
                     MD5_DIGEST_LENGTH, ntlmv2_hmacmd5);

        /* Add hmac-md5 result to the blob.
         * Note: This overwrites challenge previously written at
         * ntlmv2_response[8..15] */
        memcpy(ntlmv2_response, ntlmv2_hmacmd5, MD5_DIGEST_LENGTH);
    }
    else /* Generate NTLM response */
    {
        unsigned char key1[DES_KEY_LENGTH], key2[DES_KEY_LENGTH];
        unsigned char key3[DES_KEY_LENGTH];

        create_des_keys(md4_hash, key1);
        cipher_des_encrypt_ecb(key1, challenge, ntlm_response);

        create_des_keys(&md4_hash[DES_KEY_LENGTH - 1], key2);
        cipher_des_encrypt_ecb(key2, challenge, &ntlm_response[DES_KEY_LENGTH]);

        create_des_keys(&md4_hash[2 * (DES_KEY_LENGTH - 1)], key3);
        cipher_des_encrypt_ecb(key3, challenge,
                               &ntlm_response[DES_KEY_LENGTH * 2]);
    }


    memset(phase3, 0, sizeof(phase3));       /* clear reply */

    strcpy((char *)phase3, "NTLMSSP\0");      /* signature */
    phase3[8] = 3;     /* type 3 */

    if (ntlmv2_enabled)      /* NTLMv2 response */
    {
        add_security_buffer(0x14, ntlmv2_response, ntlmv2_blob_size + 16,
                            phase3, &phase3_bufpos);
    }
    else       /* NTLM response */
    {
        add_security_buffer(0x14, ntlm_response, 24, phase3, &phase3_bufpos);
    }

    /* username in ascii */
    add_security_buffer(0x24, username, strlen(username), phase3,
                        &phase3_bufpos);

    /* Set domain. If <domain> is empty, default domain will be used
     * (i.e. proxy's domain) */
    add_security_buffer(0x1c, domain, strlen(domain), phase3, &phase3_bufpos);

    /* other security buffers will be empty */
    phase3[0x10] = phase3_bufpos;     /* lm not used */
    phase3[0x30] = phase3_bufpos;     /* no workstation name supplied */
    phase3[0x38] = phase3_bufpos;     /* no session key */

    /* flags */
    phase3[0x3c] = 0x02; /* negotiate oem */
    phase3[0x3d] = 0x02; /* negotiate ntlm */

    return ((const char *)make_base64_string2((unsigned char *)phase3,
                                              phase3_bufpos, gc));
}