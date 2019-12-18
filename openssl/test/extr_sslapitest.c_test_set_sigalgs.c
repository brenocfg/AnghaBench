#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  connsuccess; scalar_t__ valid; int /*<<< orphan*/  liststr; int /*<<< orphan*/  listlen; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ sigalgs_list ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int OSSL_NELEM (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int SSL_CTX_set1_sigalgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_CTX_set1_sigalgs_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_set1_sigalgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_set1_sigalgs_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_le (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 TYPE_1__* testsigalgs ; 

__attribute__((used)) static int test_set_sigalgs(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    const sigalgs_list *curr;
    int testctx;

    /* Should never happen */
    if (!TEST_size_t_le((size_t)idx, OSSL_NELEM(testsigalgs) * 2))
        return 0;

    testctx = ((size_t)idx < OSSL_NELEM(testsigalgs));
    curr = testctx ? &testsigalgs[idx]
                   : &testsigalgs[idx - OSSL_NELEM(testsigalgs)];

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        return 0;

    /*
     * TODO(TLS1.3): These APIs cannot set TLSv1.3 sig algs so we just test it
     * for TLSv1.2 for now until we add a new API.
     */
    SSL_CTX_set_max_proto_version(cctx, TLS1_2_VERSION);

    if (testctx) {
        int ret;

        if (curr->list != NULL)
            ret = SSL_CTX_set1_sigalgs(cctx, curr->list, curr->listlen);
        else
            ret = SSL_CTX_set1_sigalgs_list(cctx, curr->liststr);

        if (!ret) {
            if (curr->valid)
                TEST_info("Failure setting sigalgs in SSL_CTX (%d)\n", idx);
            else
                testresult = 1;
            goto end;
        }
        if (!curr->valid) {
            TEST_info("Not-failed setting sigalgs in SSL_CTX (%d)\n", idx);
            goto end;
        }
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                      &clientssl, NULL, NULL)))
        goto end;

    if (!testctx) {
        int ret;

        if (curr->list != NULL)
            ret = SSL_set1_sigalgs(clientssl, curr->list, curr->listlen);
        else
            ret = SSL_set1_sigalgs_list(clientssl, curr->liststr);
        if (!ret) {
            if (curr->valid)
                TEST_info("Failure setting sigalgs in SSL (%d)\n", idx);
            else
                testresult = 1;
            goto end;
        }
        if (!curr->valid)
            goto end;
    }

    if (!TEST_int_eq(create_ssl_connection(serverssl, clientssl,
                                           SSL_ERROR_NONE),
                curr->connsuccess))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}