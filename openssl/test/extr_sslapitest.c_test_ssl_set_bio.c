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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int CONNTYPE_CONNECTION_FAIL ; 
 int CONNTYPE_CONNECTION_SUCCESS ; 
 int CONNTYPE_NO_CONNECTION ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int TOTAL_NO_CONN_SSL_SET_BIO_TESTS ; 
 int USE_BIO_1 ; 
 int USE_BIO_2 ; 
 int USE_DEFAULT ; 
 int /*<<< orphan*/  cert ; 
 int create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  setupbio (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_ssl_set_bio(int idx)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    BIO *bio1 = NULL;
    BIO *bio2 = NULL;
    BIO *irbio = NULL, *iwbio = NULL, *nrbio = NULL, *nwbio = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    int initrbio, initwbio, newrbio, newwbio, conntype;
    int testresult = 0;

    if (idx < TOTAL_NO_CONN_SSL_SET_BIO_TESTS) {
        initrbio = idx % 3;
        idx /= 3;
        initwbio = idx % 3;
        idx /= 3;
        newrbio = idx % 3;
        idx /= 3;
        newwbio = idx % 3;
        conntype = CONNTYPE_NO_CONNECTION;
    } else {
        idx -= TOTAL_NO_CONN_SSL_SET_BIO_TESTS;
        initrbio = initwbio = USE_DEFAULT;
        newrbio = idx % 2;
        idx /= 2;
        newwbio = idx % 2;
        idx /= 2;
        conntype = idx % 2;
    }

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    if (conntype == CONNTYPE_CONNECTION_FAIL) {
        /*
         * We won't ever get here if either TLSv1.3 or TLSv1.2 is disabled
         * because we reduced the number of tests in the definition of
         * TOTAL_CONN_FAIL_SSL_SET_BIO_TESTS to avoid this scenario. By setting
         * mismatched protocol versions we will force a connection failure.
         */
        SSL_CTX_set_min_proto_version(sctx, TLS1_3_VERSION);
        SSL_CTX_set_max_proto_version(cctx, TLS1_2_VERSION);
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL)))
        goto end;

    if (initrbio == USE_BIO_1
            || initwbio == USE_BIO_1
            || newrbio == USE_BIO_1
            || newwbio == USE_BIO_1) {
        if (!TEST_ptr(bio1 = BIO_new(BIO_s_mem())))
            goto end;
    }

    if (initrbio == USE_BIO_2
            || initwbio == USE_BIO_2
            || newrbio == USE_BIO_2
            || newwbio == USE_BIO_2) {
        if (!TEST_ptr(bio2 = BIO_new(BIO_s_mem())))
            goto end;
    }

    if (initrbio != USE_DEFAULT) {
        setupbio(&irbio, bio1, bio2, initrbio);
        setupbio(&iwbio, bio1, bio2, initwbio);
        SSL_set_bio(clientssl, irbio, iwbio);

        /*
         * We want to maintain our own refs to these BIO, so do an up ref for
         * each BIO that will have ownership transferred in the SSL_set_bio()
         * call
         */
        if (irbio != NULL)
            BIO_up_ref(irbio);
        if (iwbio != NULL && iwbio != irbio)
            BIO_up_ref(iwbio);
    }

    if (conntype != CONNTYPE_NO_CONNECTION
            && !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)
                          == (conntype == CONNTYPE_CONNECTION_SUCCESS)))
        goto end;

    setupbio(&nrbio, bio1, bio2, newrbio);
    setupbio(&nwbio, bio1, bio2, newwbio);

    /*
     * We will (maybe) transfer ownership again so do more up refs.
     * SSL_set_bio() has some really complicated ownership rules where BIOs have
     * already been set!
     */
    if (nrbio != NULL
            && nrbio != irbio
            && (nwbio != iwbio || nrbio != nwbio))
        BIO_up_ref(nrbio);
    if (nwbio != NULL
            && nwbio != nrbio
            && (nwbio != iwbio || (nwbio == iwbio && irbio == iwbio)))
        BIO_up_ref(nwbio);

    SSL_set_bio(clientssl, nrbio, nwbio);

    testresult = 1;

 end:
    BIO_free(bio1);
    BIO_free(bio2);

    /*
     * This test is checking that the ref counting for SSL_set_bio is correct.
     * If we get here and we did too many frees then we will fail in the above
     * functions. If we haven't done enough then this will only be detected in
     * a crypto-mdebug build
     */
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}