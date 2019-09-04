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
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_ADDR_new () ; 
 int /*<<< orphan*/  BIO_ADDR_rawaddress (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 unsigned short BIO_ADDR_rawport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_dgram_get_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  COOKIE_SECRET_LENGTH ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  HMAC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_dtls (int /*<<< orphan*/ *) ; 
 unsigned char* app_malloc (size_t,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int cookie_initialized ; 
 int /*<<< orphan*/  cookie_secret ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned short*,int) ; 
 int /*<<< orphan*/ * ourpeer ; 

int generate_cookie_callback(SSL *ssl, unsigned char *cookie,
                             unsigned int *cookie_len)
{
    unsigned char *buffer;
    size_t length = 0;
    unsigned short port;
    BIO_ADDR *lpeer = NULL, *peer = NULL;

    /* Initialize a random secret */
    if (!cookie_initialized) {
        if (RAND_bytes(cookie_secret, COOKIE_SECRET_LENGTH) <= 0) {
            BIO_printf(bio_err, "error setting random cookie secret\n");
            return 0;
        }
        cookie_initialized = 1;
    }

    if (SSL_is_dtls(ssl)) {
        lpeer = peer = BIO_ADDR_new();
        if (peer == NULL) {
            BIO_printf(bio_err, "memory full\n");
            return 0;
        }

        /* Read peer information */
        (void)BIO_dgram_get_peer(SSL_get_rbio(ssl), peer);
    } else {
        peer = ourpeer;
    }

    /* Create buffer with peer's address and port */
    if (!BIO_ADDR_rawaddress(peer, NULL, &length)) {
        BIO_printf(bio_err, "Failed getting peer address\n");
        return 0;
    }
    OPENSSL_assert(length != 0);
    port = BIO_ADDR_rawport(peer);
    length += sizeof(port);
    buffer = app_malloc(length, "cookie generate buffer");

    memcpy(buffer, &port, sizeof(port));
    BIO_ADDR_rawaddress(peer, buffer + sizeof(port), NULL);

    /* Calculate HMAC of buffer using the secret */
    HMAC(EVP_sha1(), cookie_secret, COOKIE_SECRET_LENGTH,
         buffer, length, cookie, cookie_len);

    OPENSSL_free(buffer);
    BIO_ADDR_free(lpeer);

    return 1;
}