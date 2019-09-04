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
 int /*<<< orphan*/  MSG1 ; 
 int /*<<< orphan*/  MSG2 ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_NOT_SENT ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_ERROR ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_FINISH ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_early_data (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_write_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_early_data_tls1_2(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    unsigned char buf[20];
    size_t readbytes, written;

    if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl,
                                        &serverssl, NULL, idx)))
        goto end;

    /* Write some data - should block due to handshake with server */
    SSL_set_max_proto_version(clientssl, TLS1_2_VERSION);
    SSL_set_connect_state(clientssl);
    if (!TEST_false(SSL_write_ex(clientssl, MSG1, strlen(MSG1), &written)))
        goto end;

    /*
     * Server should do TLSv1.2 handshake. First it will block waiting for more
     * messages from client after ServerDone. Then SSL_read_early_data should
     * finish and detect that early data has not been sent
     */
    if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                         &readbytes),
                     SSL_READ_EARLY_DATA_ERROR))
        goto end;

    /*
     * Continue writing the message we started earlier. Will still block waiting
     * for the CCS/Finished from server
     */
    if (!TEST_false(SSL_write_ex(clientssl, MSG1, strlen(MSG1), &written))
            || !TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                                &readbytes),
                            SSL_READ_EARLY_DATA_FINISH)
            || !TEST_size_t_eq(readbytes, 0)
            || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                            SSL_EARLY_DATA_NOT_SENT))
        goto end;

    /* Continue writing the message we started earlier */
    if (!TEST_true(SSL_write_ex(clientssl, MSG1, strlen(MSG1), &written))
            || !TEST_size_t_eq(written, strlen(MSG1))
            || !TEST_int_eq(SSL_get_early_data_status(clientssl),
                            SSL_EARLY_DATA_NOT_SENT)
            || !TEST_true(SSL_read_ex(serverssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG1, strlen(MSG1))
            || !TEST_true(SSL_write_ex(serverssl, MSG2, strlen(MSG2), &written))
            || !TEST_size_t_eq(written, strlen(MSG2))
            || !SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes)
            || !TEST_mem_eq(buf, readbytes, MSG2, strlen(MSG2)))
        goto end;

    testresult = 1;

 end:
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}