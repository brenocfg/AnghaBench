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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG1 ; 
 int /*<<< orphan*/  MSG2 ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_REJECTED ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_write_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  SSL_write_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_early_data_not_expected(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    SSL_SESSION *sess = NULL;
    unsigned char buf[20];
    size_t readbytes, written;

    if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl,
                                        &serverssl, &sess, idx)))
        goto end;

    /* Write some early data */
    if (!TEST_true(SSL_write_early_data(clientssl, MSG1, strlen(MSG1),
                                        &written)))
        goto end;

    /*
     * Server should skip over early data and then block waiting for client to
     * continue handshake
     */
    if (!TEST_int_le(SSL_accept(serverssl), 0)
     || !TEST_int_gt(SSL_connect(clientssl), 0)
     || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                     SSL_EARLY_DATA_REJECTED)
     || !TEST_int_gt(SSL_accept(serverssl), 0)
     || !TEST_int_eq(SSL_get_early_data_status(clientssl),
                     SSL_EARLY_DATA_REJECTED))
        goto end;

    /* Send some normal data from client to server */
    if (!TEST_true(SSL_write_ex(clientssl, MSG2, strlen(MSG2), &written))
            || !TEST_size_t_eq(written, strlen(MSG2)))
        goto end;

    if (!TEST_true(SSL_read_ex(serverssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG2, strlen(MSG2)))
        goto end;

    testresult = 1;

 end:
    SSL_SESSION_free(sess);
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}