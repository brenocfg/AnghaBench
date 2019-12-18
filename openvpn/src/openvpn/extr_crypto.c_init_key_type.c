#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct key_type {int cipher_length; scalar_t__ hmac_length; int /*<<< orphan*/  digest; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char const*) ; 
 int /*<<< orphan*/  CLEAR (struct key_type) ; 
 int MAX_CIPHER_KEY_LENGTH ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ OPENVPN_MAX_CIPHER_BLOCK_SIZE ; 
 scalar_t__ OPENVPN_MAX_HMAC_SIZE ; 
 scalar_t__ cipher_kt_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipher_kt_get (int /*<<< orphan*/ ) ; 
 int cipher_kt_key_size (int /*<<< orphan*/ ) ; 
 int cipher_kt_mode_aead (int /*<<< orphan*/ ) ; 
 scalar_t__ cipher_kt_mode_cbc (int /*<<< orphan*/ ) ; 
 scalar_t__ cipher_kt_mode_ofb_cfb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_kt_get (char const*) ; 
 scalar_t__ md_kt_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  translate_cipher_name_from_openvpn (char const*) ; 

void
init_key_type(struct key_type *kt, const char *ciphername,
              const char *authname, int keysize, bool tls_mode, bool warn)
{
    bool aead_cipher = false;

    ASSERT(ciphername);
    ASSERT(authname);

    CLEAR(*kt);
    if (strcmp(ciphername, "none") != 0)
    {
        kt->cipher = cipher_kt_get(translate_cipher_name_from_openvpn(ciphername));
        if (!kt->cipher)
        {
            msg(M_FATAL, "Cipher %s not supported", ciphername);
        }

        kt->cipher_length = cipher_kt_key_size(kt->cipher);
        if (keysize > 0 && keysize <= MAX_CIPHER_KEY_LENGTH)
        {
            kt->cipher_length = keysize;
        }

        /* check legal cipher mode */
        aead_cipher = cipher_kt_mode_aead(kt->cipher);
        if (!(cipher_kt_mode_cbc(kt->cipher)
              || (tls_mode && aead_cipher)
#ifdef ENABLE_OFB_CFB_MODE
              || (tls_mode && cipher_kt_mode_ofb_cfb(kt->cipher))
#endif
              ))
        {
            msg(M_FATAL, "Cipher '%s' mode not supported", ciphername);
        }

        if (OPENVPN_MAX_CIPHER_BLOCK_SIZE < cipher_kt_block_size(kt->cipher))
        {
            msg(M_FATAL, "Cipher '%s' not allowed: block size too big.", ciphername);
        }
    }
    else
    {
        if (warn)
        {
            msg(M_WARN, "******* WARNING *******: '--cipher none' was specified. "
                "This means NO encryption will be performed and tunnelled "
                "data WILL be transmitted in clear text over the network! "
                "PLEASE DO RECONSIDER THIS SETTING!");
        }
    }
    if (strcmp(authname, "none") != 0)
    {
        if (!aead_cipher) /* Ignore auth for AEAD ciphers */
        {
            kt->digest = md_kt_get(authname);
            kt->hmac_length = md_kt_size(kt->digest);

            if (OPENVPN_MAX_HMAC_SIZE < kt->hmac_length)
            {
                msg(M_FATAL, "HMAC '%s' not allowed: digest size too big.", authname);
            }
        }
    }
    else if (!aead_cipher)
    {
        if (warn)
        {
            msg(M_WARN, "******* WARNING *******: '--auth none' was specified. "
                "This means no authentication will be performed on received "
                "packets, meaning you CANNOT trust that the data received by "
                "the remote side have NOT been manipulated. "
                "PLEASE DO RECONSIDER THIS SETTING!");
        }
    }
}