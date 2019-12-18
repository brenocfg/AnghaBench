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

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_OP_NO_EXTENDED_MASTER_SECRET ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_extms_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_no_ems(void)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;

    if (!create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                             TLS1_VERSION, TLS1_2_VERSION,
                             &sctx, &cctx, cert, privkey)) {
        printf("Unable to create SSL_CTX pair\n");
        goto end;
    }

    SSL_CTX_set_options(sctx, SSL_OP_NO_EXTENDED_MASTER_SECRET);

    if (!create_ssl_objects(sctx, cctx, &serverssl, &clientssl, NULL, NULL)) {
        printf("Unable to create SSL objects\n");
        goto end;
    }

    if (!create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE)) {
        printf("Creating SSL connection failed\n");
        goto end;
    }

    if (SSL_get_extms_support(serverssl)) {
        printf("Server reports Extended Master Secret support\n");
        goto end;
    }

    if (SSL_get_extms_support(clientssl)) {
        printf("Client reports Extended Master Secret support\n");
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