#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* buf; size_t tls_aad_len; int /*<<< orphan*/  enc; scalar_t__ tls_enc_records; } ;
typedef  TYPE_1__ PROV_GCM_CTX ;

/* Variables and functions */
 size_t EVP_AEAD_TLS1_AAD_LEN ; 
 size_t EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 size_t EVP_GCM_TLS_TAG_LEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int gcm_tls_init(PROV_GCM_CTX *dat, unsigned char *aad, size_t aad_len)
{
    unsigned char *buf;
    size_t len;

    if (aad_len != EVP_AEAD_TLS1_AAD_LEN)
       return 0;

    /* Save the aad for later use. */
    buf = dat->buf;
    memcpy(buf, aad, aad_len);
    dat->tls_aad_len = aad_len;
    dat->tls_enc_records = 0;

    len = buf[aad_len - 2] << 8 | buf[aad_len - 1];
    /* Correct length for explicit iv. */
    if (len < EVP_GCM_TLS_EXPLICIT_IV_LEN)
        return 0;
    len -= EVP_GCM_TLS_EXPLICIT_IV_LEN;

    /* If decrypting correct for tag too. */
    if (!dat->enc) {
        if (len < EVP_GCM_TLS_TAG_LEN)
            return 0;
        len -= EVP_GCM_TLS_TAG_LEN;
    }
    buf[aad_len - 2] = (unsigned char)(len >> 8);
    buf[aad_len - 1] = (unsigned char)(len & 0xff);
    /* Extra padding: tag appended to record. */
    return EVP_GCM_TLS_TAG_LEN;
}