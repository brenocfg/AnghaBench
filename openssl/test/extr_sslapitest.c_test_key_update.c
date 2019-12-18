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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int NUM_KEY_UPDATE_MESSAGES ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NOT_REQUESTED ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_REQUESTED ; 
 int /*<<< orphan*/  SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_key_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SSL_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_key_update(void)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0, i, j;
    char buf[20];
    static char *mess = "A test message";

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_3_VERSION,
                                       0,
                                       &sctx, &cctx, cert, privkey))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    for (j = 0; j < 2; j++) {
        /* Send lots of KeyUpdate messages */
        for (i = 0; i < NUM_KEY_UPDATE_MESSAGES; i++) {
            if (!TEST_true(SSL_key_update(clientssl,
                                          (j == 0)
                                          ? SSL_KEY_UPDATE_NOT_REQUESTED
                                          : SSL_KEY_UPDATE_REQUESTED))
                    || !TEST_true(SSL_do_handshake(clientssl)))
                goto end;
        }

        /* Check that sending and receiving app data is ok */
        if (!TEST_int_eq(SSL_write(clientssl, mess, strlen(mess)), strlen(mess))
                || !TEST_int_eq(SSL_read(serverssl, buf, sizeof(buf)),
                                         strlen(mess)))
            goto end;

        if (!TEST_int_eq(SSL_write(serverssl, mess, strlen(mess)), strlen(mess))
                || !TEST_int_eq(SSL_read(clientssl, buf, sizeof(buf)),
                                         strlen(mess)))
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