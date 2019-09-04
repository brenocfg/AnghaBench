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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  SSL3_RT_APPLICATION_DATA ; 
 int /*<<< orphan*/  SSL3_RT_HANDSHAKE ; 
 scalar_t__ SSL3_RT_MAX_COMPRESSED_OVERHEAD ; 
 size_t SSL3_RT_MAX_ENCRYPTED_LENGTH ; 
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
 size_t SSL3_RT_MAX_TLS13_ENCRYPTED_LENGTH ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int TEST_ENCRYPTED_OVERFLOW_TLS1_2_NOT_OK ; 
 int TEST_ENCRYPTED_OVERFLOW_TLS1_2_OK ; 
 int TEST_ENCRYPTED_OVERFLOW_TLS1_3_NOT_OK ; 
 int TEST_ENCRYPTED_OVERFLOW_TLS1_3_OK ; 
 int TEST_PLAINTEXT_OVERFLOW_NOT_OK ; 
 int TEST_PLAINTEXT_OVERFLOW_OK ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int TLS1_2_VERSION ; 
 int TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_due_to_record_overflow (int) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  write_record (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_record_overflow(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    size_t len = 0;
    size_t written;
    int overf_expected;
    unsigned char buf;
    BIO *serverbio;
    int recversion;

#ifdef OPENSSL_NO_TLS1_2
    if (idx == TEST_ENCRYPTED_OVERFLOW_TLS1_2_OK
            || idx == TEST_ENCRYPTED_OVERFLOW_TLS1_2_NOT_OK)
        return 1;
#endif
#ifdef OPENSSL_NO_TLS1_3
    if (idx == TEST_ENCRYPTED_OVERFLOW_TLS1_3_OK
            || idx == TEST_ENCRYPTED_OVERFLOW_TLS1_3_NOT_OK)
        return 1;
#endif

    ERR_clear_error();

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    if (idx == TEST_ENCRYPTED_OVERFLOW_TLS1_2_OK
            || idx == TEST_ENCRYPTED_OVERFLOW_TLS1_2_NOT_OK) {
        len = SSL3_RT_MAX_ENCRYPTED_LENGTH;
#ifndef OPENSSL_NO_COMP
        len -= SSL3_RT_MAX_COMPRESSED_OVERHEAD;
#endif
        SSL_CTX_set_max_proto_version(sctx, TLS1_2_VERSION);
    } else if (idx == TEST_ENCRYPTED_OVERFLOW_TLS1_3_OK
               || idx == TEST_ENCRYPTED_OVERFLOW_TLS1_3_NOT_OK) {
        len = SSL3_RT_MAX_TLS13_ENCRYPTED_LENGTH;
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL)))
        goto end;

    serverbio = SSL_get_rbio(serverssl);

    if (idx == TEST_PLAINTEXT_OVERFLOW_OK
            || idx == TEST_PLAINTEXT_OVERFLOW_NOT_OK) {
        len = SSL3_RT_MAX_PLAIN_LENGTH;

        if (idx == TEST_PLAINTEXT_OVERFLOW_NOT_OK)
            len++;

        if (!TEST_true(write_record(serverbio, len,
                                    SSL3_RT_HANDSHAKE, TLS1_VERSION)))
            goto end;

        if (!TEST_int_le(SSL_accept(serverssl), 0))
            goto end;

        overf_expected = (idx == TEST_PLAINTEXT_OVERFLOW_OK) ? 0 : 1;
        if (!TEST_int_eq(fail_due_to_record_overflow(0), overf_expected))
            goto end;

        goto success;
    }

    if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                         SSL_ERROR_NONE)))
        goto end;

    if (idx == TEST_ENCRYPTED_OVERFLOW_TLS1_2_NOT_OK
            || idx == TEST_ENCRYPTED_OVERFLOW_TLS1_3_NOT_OK) {
        overf_expected = 1;
        len++;
    } else {
        overf_expected = 0;
    }

    recversion = TLS1_2_VERSION;

    if (!TEST_true(write_record(serverbio, len, SSL3_RT_APPLICATION_DATA,
                                recversion)))
        goto end;

    if (!TEST_false(SSL_read_ex(serverssl, &buf, sizeof(buf), &written)))
        goto end;

    if (!TEST_int_eq(fail_due_to_record_overflow(1), overf_expected))
        goto end;

 success:
    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}