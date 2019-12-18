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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  BIO_write_ex (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned char* MSG1 ; 
 unsigned char* MSG2 ; 
 unsigned char* MSG3 ; 
 unsigned char* MSG4 ; 
 unsigned char* MSG5 ; 
 unsigned char* MSG6 ; 
 unsigned char* MSG7 ; 
 unsigned char SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_ERROR ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_FINISH ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_SUCCESS ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_early_data (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_write_early_data (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*) ; 
 int /*<<< orphan*/  SSL_write_ex (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_gt (size_t,unsigned char) ; 
 int /*<<< orphan*/  TEST_size_t_lt (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ find_session_cb_cnt ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 size_t strlen (unsigned char*) ; 
 scalar_t__ use_session_cb_cnt ; 

__attribute__((used)) static int test_early_data_read_write(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    SSL_SESSION *sess = NULL;
    unsigned char buf[20], data[1024];
    size_t readbytes, written, eoedlen, rawread, rawwritten;
    BIO *rbio;

    if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl,
                                        &serverssl, &sess, idx)))
        goto end;

    /* Write and read some early data */
    if (!TEST_true(SSL_write_early_data(clientssl, MSG1, strlen(MSG1),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG1))
            || !TEST_int_eq(SSL_read_early_data(serverssl, buf,
                                                sizeof(buf), &readbytes),
                            SSL_READ_EARLY_DATA_SUCCESS)
            || !TEST_mem_eq(MSG1, readbytes, buf, strlen(MSG1))
            || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                            SSL_EARLY_DATA_ACCEPTED))
        goto end;

    /*
     * Server should be able to write data, and client should be able to
     * read it.
     */
    if (!TEST_true(SSL_write_early_data(serverssl, MSG2, strlen(MSG2),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG2))
            || !TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG2, strlen(MSG2)))
        goto end;

    /* Even after reading normal data, client should be able write early data */
    if (!TEST_true(SSL_write_early_data(clientssl, MSG3, strlen(MSG3),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG3)))
        goto end;

    /* Server should still be able read early data after writing data */
    if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                         &readbytes),
                     SSL_READ_EARLY_DATA_SUCCESS)
            || !TEST_mem_eq(buf, readbytes, MSG3, strlen(MSG3)))
        goto end;

    /* Write more data from server and read it from client */
    if (!TEST_true(SSL_write_early_data(serverssl, MSG4, strlen(MSG4),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG4))
            || !TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG4, strlen(MSG4)))
        goto end;

    /*
     * If client writes normal data it should mean writing early data is no
     * longer possible.
     */
    if (!TEST_true(SSL_write_ex(clientssl, MSG5, strlen(MSG5), &written))
            || !TEST_size_t_eq(written, strlen(MSG5))
            || !TEST_int_eq(SSL_get_early_data_status(clientssl),
                            SSL_EARLY_DATA_ACCEPTED))
        goto end;

    /*
     * At this point the client has written EndOfEarlyData, ClientFinished and
     * normal (fully protected) data. We are going to cause a delay between the
     * arrival of EndOfEarlyData and ClientFinished. We read out all the data
     * in the read BIO, and then just put back the EndOfEarlyData message.
     */
    rbio = SSL_get_rbio(serverssl);
    if (!TEST_true(BIO_read_ex(rbio, data, sizeof(data), &rawread))
            || !TEST_size_t_lt(rawread, sizeof(data))
            || !TEST_size_t_gt(rawread, SSL3_RT_HEADER_LENGTH))
        goto end;

    /* Record length is in the 4th and 5th bytes of the record header */
    eoedlen = SSL3_RT_HEADER_LENGTH + (data[3] << 8 | data[4]);
    if (!TEST_true(BIO_write_ex(rbio, data, eoedlen, &rawwritten))
            || !TEST_size_t_eq(rawwritten, eoedlen))
        goto end;

    /* Server should be told that there is no more early data */
    if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                         &readbytes),
                     SSL_READ_EARLY_DATA_FINISH)
            || !TEST_size_t_eq(readbytes, 0))
        goto end;

    /*
     * Server has not finished init yet, so should still be able to write early
     * data.
     */
    if (!TEST_true(SSL_write_early_data(serverssl, MSG6, strlen(MSG6),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG6)))
        goto end;

    /* Push the ClientFinished and the normal data back into the server rbio */
    if (!TEST_true(BIO_write_ex(rbio, data + eoedlen, rawread - eoedlen,
                                &rawwritten))
            || !TEST_size_t_eq(rawwritten, rawread - eoedlen))
        goto end;

    /* Server should be able to read normal data */
    if (!TEST_true(SSL_read_ex(serverssl, buf, sizeof(buf), &readbytes))
            || !TEST_size_t_eq(readbytes, strlen(MSG5)))
        goto end;

    /* Client and server should not be able to write/read early data now */
    if (!TEST_false(SSL_write_early_data(clientssl, MSG6, strlen(MSG6),
                                         &written)))
        goto end;
    ERR_clear_error();
    if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                         &readbytes),
                     SSL_READ_EARLY_DATA_ERROR))
        goto end;
    ERR_clear_error();

    /* Client should be able to read the data sent by the server */
    if (!TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG6, strlen(MSG6)))
        goto end;

    /*
     * Make sure we process the two NewSessionTickets. These arrive
     * post-handshake. We attempt reads which we do not expect to return any
     * data.
     */
    if (!TEST_false(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_false(SSL_read_ex(clientssl, buf, sizeof(buf),
                           &readbytes)))
        goto end;

    /* Server should be able to write normal data */
    if (!TEST_true(SSL_write_ex(serverssl, MSG7, strlen(MSG7), &written))
            || !TEST_size_t_eq(written, strlen(MSG7))
            || !TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_mem_eq(buf, readbytes, MSG7, strlen(MSG7)))
        goto end;

    SSL_SESSION_free(sess);
    sess = SSL_get1_session(clientssl);
    use_session_cb_cnt = 0;
    find_session_cb_cnt = 0;

    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                      &clientssl, NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl, sess)))
        goto end;

    /* Write and read some early data */
    if (!TEST_true(SSL_write_early_data(clientssl, MSG1, strlen(MSG1),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG1))
            || !TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                                &readbytes),
                            SSL_READ_EARLY_DATA_SUCCESS)
            || !TEST_mem_eq(buf, readbytes, MSG1, strlen(MSG1)))
        goto end;

    if (!TEST_int_gt(SSL_connect(clientssl), 0)
            || !TEST_int_gt(SSL_accept(serverssl), 0))
        goto end;

    /* Client and server should not be able to write/read early data now */
    if (!TEST_false(SSL_write_early_data(clientssl, MSG6, strlen(MSG6),
                                         &written)))
        goto end;
    ERR_clear_error();
    if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                         &readbytes),
                     SSL_READ_EARLY_DATA_ERROR))
        goto end;
    ERR_clear_error();

    /* Client and server should be able to write/read normal data */
    if (!TEST_true(SSL_write_ex(clientssl, MSG5, strlen(MSG5), &written))
            || !TEST_size_t_eq(written, strlen(MSG5))
            || !TEST_true(SSL_read_ex(serverssl, buf, sizeof(buf), &readbytes))
            || !TEST_size_t_eq(readbytes, strlen(MSG5)))
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