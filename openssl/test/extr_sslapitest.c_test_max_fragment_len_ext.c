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
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_tlsext_max_fragment_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  TLS_method () ; 
 int get_MFL_from_client_hello (int /*<<< orphan*/ *,int*) ; 
 int* max_fragment_len_test ; 

__attribute__((used)) static int test_max_fragment_len_ext(int idx_tst)
{
    SSL_CTX *ctx;
    SSL *con = NULL;
    int testresult = 0, MFL_mode = 0;
    BIO *rbio, *wbio;

    ctx = SSL_CTX_new(TLS_method());
    if (!TEST_ptr(ctx))
        goto end;

    if (!TEST_true(SSL_CTX_set_tlsext_max_fragment_length(
                   ctx, max_fragment_len_test[idx_tst])))
        goto end;

    con = SSL_new(ctx);
    if (!TEST_ptr(con))
        goto end;

    rbio = BIO_new(BIO_s_mem());
    wbio = BIO_new(BIO_s_mem());
    if (!TEST_ptr(rbio)|| !TEST_ptr(wbio)) {
        BIO_free(rbio);
        BIO_free(wbio);
        goto end;
    }

    SSL_set_bio(con, rbio, wbio);
    SSL_set_connect_state(con);

    if (!TEST_int_le(SSL_connect(con), 0)) {
        /* This shouldn't succeed because we don't have a server! */
        goto end;
    }

    if (!TEST_true(get_MFL_from_client_hello(wbio, &MFL_mode)))
        /* no MFL in client hello */
        goto end;
    if (!TEST_true(max_fragment_len_test[idx_tst] == MFL_mode))
        goto end;

    testresult = 1;

end:
    SSL_free(con);
    SSL_CTX_free(ctx);

    return testresult;
}