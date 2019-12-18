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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/ * SSL_CIPHER_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_SESSION_new () ; 
 int /*<<< orphan*/  SSL_SESSION_set1_master_key (int /*<<< orphan*/ *,unsigned char*,long) ; 
 int /*<<< orphan*/  SSL_SESSION_set_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_SESSION_set_protocol_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  psk_identity ; 
 int /*<<< orphan*/  psk_key ; 
 int /*<<< orphan*/ * psksess ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls13_aes128gcmsha256_id ; 

__attribute__((used)) static int psk_find_session_cb(SSL *ssl, const unsigned char *identity,
                               size_t identity_len, SSL_SESSION **sess)
{
    SSL_SESSION *tmpsess = NULL;
    unsigned char *key;
    long key_len;
    const SSL_CIPHER *cipher = NULL;

    if (strlen(psk_identity) != identity_len
            || memcmp(psk_identity, identity, identity_len) != 0) {
        *sess = NULL;
        return 1;
    }

    if (psksess != NULL) {
        SSL_SESSION_up_ref(psksess);
        *sess = psksess;
        return 1;
    }

    key = OPENSSL_hexstr2buf(psk_key, &key_len);
    if (key == NULL) {
        BIO_printf(bio_err, "Could not convert PSK key '%s' to buffer\n",
                   psk_key);
        return 0;
    }

    /* We default to SHA256 */
    cipher = SSL_CIPHER_find(ssl, tls13_aes128gcmsha256_id);
    if (cipher == NULL) {
        BIO_printf(bio_err, "Error finding suitable ciphersuite\n");
        OPENSSL_free(key);
        return 0;
    }

    tmpsess = SSL_SESSION_new();
    if (tmpsess == NULL
            || !SSL_SESSION_set1_master_key(tmpsess, key, key_len)
            || !SSL_SESSION_set_cipher(tmpsess, cipher)
            || !SSL_SESSION_set_protocol_version(tmpsess, SSL_version(ssl))) {
        OPENSSL_free(key);
        return 0;
    }
    OPENSSL_free(key);
    *sess = tmpsess;

    return 1;
}