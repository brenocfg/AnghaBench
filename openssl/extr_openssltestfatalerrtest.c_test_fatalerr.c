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
typedef  int /*<<< orphan*/  dummyrec ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int SSL_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_error (char*,char*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int test_fatalerr(void)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *sssl = NULL, *cssl = NULL;
    const char *msg = "Dummy";
    BIO *wbio = NULL;
    int ret = 0, len;
    char buf[80];
    unsigned char dummyrec[] = {
        0x17, 0x03, 0x03, 0x00, 0x05, 'D', 'u', 'm', 'm', 'y'
    };

    if (!TEST_true(create_ssl_ctx_pair(TLS_method(), TLS_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        goto err;

    /*
     * Deliberately set the cipher lists for client and server to be different
     * to force a handshake failure.
     */
    if (!TEST_true(SSL_CTX_set_cipher_list(sctx, "AES128-SHA"))
            || !TEST_true(SSL_CTX_set_cipher_list(cctx, "AES256-SHA"))
            || !TEST_true(SSL_CTX_set_ciphersuites(sctx,
                                                   "TLS_AES_128_GCM_SHA256"))
            || !TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                                   "TLS_AES_256_GCM_SHA384"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &sssl, &cssl, NULL,
                          NULL)))
        goto err;

    wbio = SSL_get_wbio(cssl);
    if (!TEST_ptr(wbio)) {
        printf("Unexpected NULL bio received\n");
        goto err;
    }

    /* Connection should fail */
    if (!TEST_false(create_ssl_connection(sssl, cssl, SSL_ERROR_NONE)))
        goto err;

    ERR_clear_error();

    /* Inject a plaintext record from client to server */
    if (!TEST_int_gt(BIO_write(wbio, dummyrec, sizeof(dummyrec)), 0))
        goto err;

    /* SSL_read()/SSL_write should fail because of a previous fatal error */
    if (!TEST_int_le(len = SSL_read(sssl, buf, sizeof(buf) - 1), 0)) {
        buf[len] = '\0';
        TEST_error("Unexpected success reading data: %s\n", buf);
        goto err;
    }
    if (!TEST_int_le(SSL_write(sssl, msg, strlen(msg)), 0))
        goto err;

    ret = 1;
 err:
    SSL_free(sssl);
    SSL_free(cssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return ret;
}