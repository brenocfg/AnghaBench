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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  shared; int /*<<< orphan*/ * srvrtls13ciphers; int /*<<< orphan*/  srvrciphers; int /*<<< orphan*/ * clnttls13ciphers; int /*<<< orphan*/  clntciphers; int /*<<< orphan*/  maxprot; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_shared_ciphers (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TEST_info (char*,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 TYPE_1__* shared_ciphers_data ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_ssl_get_shared_ciphers(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    char buf[1024];

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_VERSION,
                                       shared_ciphers_data[tst].maxprot,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    if (!TEST_true(SSL_CTX_set_cipher_list(cctx,
                                        shared_ciphers_data[tst].clntciphers))
            || (shared_ciphers_data[tst].clnttls13ciphers != NULL
                && !TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                    shared_ciphers_data[tst].clnttls13ciphers)))
            || !TEST_true(SSL_CTX_set_cipher_list(sctx,
                                        shared_ciphers_data[tst].srvrciphers))
            || (shared_ciphers_data[tst].srvrtls13ciphers != NULL
                && !TEST_true(SSL_CTX_set_ciphersuites(sctx,
                                    shared_ciphers_data[tst].srvrtls13ciphers))))
        goto end;


    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    if (!TEST_ptr(SSL_get_shared_ciphers(serverssl, buf, sizeof(buf)))
            || !TEST_int_eq(strcmp(buf, shared_ciphers_data[tst].shared), 0)) {
        TEST_info("Shared ciphers are: %s\n", buf);
        goto end;
    }

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}