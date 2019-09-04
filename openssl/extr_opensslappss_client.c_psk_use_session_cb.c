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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/ * SSL_CIPHER_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* SSL_CIPHER_get_handshake_digest (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_SESSION_get0_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_SESSION_new () ; 
 int /*<<< orphan*/  SSL_SESSION_set1_master_key (int /*<<< orphan*/ *,unsigned char*,long) ; 
 int /*<<< orphan*/  SSL_SESSION_set_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_SESSION_set_protocol_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ psk_identity ; 
 int /*<<< orphan*/  psk_key ; 
 int /*<<< orphan*/ * psksess ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  tls13_aes128gcmsha256_id ; 

__attribute__((used)) static int psk_use_session_cb(SSL *s, const EVP_MD *md,
                              const unsigned char **id, size_t *idlen,
                              SSL_SESSION **sess)
{
    SSL_SESSION *usesess = NULL;
    const SSL_CIPHER *cipher = NULL;

    if (psksess != NULL) {
        SSL_SESSION_up_ref(psksess);
        usesess = psksess;
    } else {
        long key_len;
        unsigned char *key = OPENSSL_hexstr2buf(psk_key, &key_len);

        if (key == NULL) {
            BIO_printf(bio_err, "Could not convert PSK key '%s' to buffer\n",
                       psk_key);
            return 0;
        }

        /* We default to SHA-256 */
        cipher = SSL_CIPHER_find(s, tls13_aes128gcmsha256_id);
        if (cipher == NULL) {
            BIO_printf(bio_err, "Error finding suitable ciphersuite\n");
            OPENSSL_free(key);
            return 0;
        }

        usesess = SSL_SESSION_new();
        if (usesess == NULL
                || !SSL_SESSION_set1_master_key(usesess, key, key_len)
                || !SSL_SESSION_set_cipher(usesess, cipher)
                || !SSL_SESSION_set_protocol_version(usesess, TLS1_3_VERSION)) {
            OPENSSL_free(key);
            goto err;
        }
        OPENSSL_free(key);
    }

    cipher = SSL_SESSION_get0_cipher(usesess);
    if (cipher == NULL)
        goto err;

    if (md != NULL && SSL_CIPHER_get_handshake_digest(cipher) != md) {
        /* PSK not usable, ignore it */
        *id = NULL;
        *idlen = 0;
        *sess = NULL;
        SSL_SESSION_free(usesess);
    } else {
        *sess = usesess;
        *id = (unsigned char *)psk_identity;
        *idlen = strlen(psk_identity);
    }

    return 1;

 err:
    SSL_SESSION_free(usesess);
    return 0;
}