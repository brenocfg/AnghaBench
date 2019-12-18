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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_METHOD ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int NUM_EXTRA_CERTS ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_CTX_add_extra_chain_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_read_ahead (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int execute_test_large_message(const SSL_METHOD *smeth,
                                      const SSL_METHOD *cmeth,
                                      int min_version, int max_version,
                                      int read_ahead)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    int i;
    BIO *certbio = NULL;
    X509 *chaincert = NULL;
    int certlen;

    if (!TEST_ptr(certbio = BIO_new_file(cert, "r")))
        goto end;
    chaincert = PEM_read_bio_X509(certbio, NULL, NULL, NULL);
    BIO_free(certbio);
    certbio = NULL;
    if (!TEST_ptr(chaincert))
        goto end;

    if (!TEST_true(create_ssl_ctx_pair(smeth, cmeth, min_version, max_version,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    if (read_ahead) {
        /*
         * Test that read_ahead works correctly when dealing with large
         * records
         */
        SSL_CTX_set_read_ahead(cctx, 1);
    }

    /*
     * We assume the supplied certificate is big enough so that if we add
     * NUM_EXTRA_CERTS it will make the overall message large enough. The
     * default buffer size is requested to be 16k, but due to the way BUF_MEM
     * works, it ends up allocating a little over 21k (16 * 4/3). So, in this
     * test we need to have a message larger than that.
     */
    certlen = i2d_X509(chaincert, NULL);
    OPENSSL_assert(certlen * NUM_EXTRA_CERTS >
                   (SSL3_RT_MAX_PLAIN_LENGTH * 4) / 3);
    for (i = 0; i < NUM_EXTRA_CERTS; i++) {
        if (!X509_up_ref(chaincert))
            goto end;
        if (!SSL_CTX_add_extra_chain_cert(sctx, chaincert)) {
            X509_free(chaincert);
            goto end;
        }
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    /*
     * Calling SSL_clear() first is not required but this tests that SSL_clear()
     * doesn't leak (when using enable-crypto-mdebug).
     */
    if (!TEST_true(SSL_clear(serverssl)))
        goto end;

    testresult = 1;
 end:
    X509_free(chaincert);
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}