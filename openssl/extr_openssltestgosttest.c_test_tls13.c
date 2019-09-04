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
struct TYPE_2__ {scalar_t__ certnum; scalar_t__ expected_prot; int /*<<< orphan*/  cipher; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert1 ; 
 int /*<<< orphan*/  cert2 ; 
 TYPE_1__* ciphers ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey1 ; 
 int /*<<< orphan*/  privkey2 ; 

__attribute__((used)) static int test_tls13(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_VERSION,
                                       0,
                                       &sctx, &cctx,
                                       ciphers[idx].certnum == 0 ? cert1
                                                                 : cert2,
                                       ciphers[idx].certnum == 0 ? privkey1
                                                                 : privkey2)))
        goto end;

    if (!TEST_true(SSL_CTX_set_cipher_list(cctx, ciphers[idx].cipher))
            || !TEST_true(SSL_CTX_set_cipher_list(sctx, ciphers[idx].cipher))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL)))
        goto end;

    if (ciphers[idx].expected_prot == 0) {
        if (!TEST_false(create_ssl_connection(serverssl, clientssl,
                                              SSL_ERROR_NONE)))
            goto end;
    } else {
        if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                             SSL_ERROR_NONE))
                || !TEST_int_eq(SSL_version(clientssl),
                                ciphers[idx].expected_prot))
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