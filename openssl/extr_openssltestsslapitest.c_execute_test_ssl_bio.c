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
typedef  scalar_t__ bio_change_t ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLOSE ; 
 int /*<<< orphan*/  BIO_f_ssl () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CHANGE_RBIO ; 
 scalar_t__ NO_BIO_CHANGE ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set0_rbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set0_wbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLS_method () ; 

__attribute__((used)) static int execute_test_ssl_bio(int pop_ssl, bio_change_t change_bio)
{
    BIO *sslbio = NULL, *membio1 = NULL, *membio2 = NULL;
    SSL_CTX *ctx;
    SSL *ssl = NULL;
    int testresult = 0;

    if (!TEST_ptr(ctx = SSL_CTX_new(TLS_method()))
            || !TEST_ptr(ssl = SSL_new(ctx))
            || !TEST_ptr(sslbio = BIO_new(BIO_f_ssl()))
            || !TEST_ptr(membio1 = BIO_new(BIO_s_mem())))
        goto end;

    BIO_set_ssl(sslbio, ssl, BIO_CLOSE);

    /*
     * If anything goes wrong here then we could leak memory, so this will
     * be caught in a crypto-mdebug build
     */
    BIO_push(sslbio, membio1);

    /* Verify changing the rbio/wbio directly does not cause leaks */
    if (change_bio != NO_BIO_CHANGE) {
        if (!TEST_ptr(membio2 = BIO_new(BIO_s_mem())))
            goto end;
        if (change_bio == CHANGE_RBIO)
            SSL_set0_rbio(ssl, membio2);
        else
            SSL_set0_wbio(ssl, membio2);
    }
    ssl = NULL;

    if (pop_ssl)
        BIO_pop(sslbio);
    else
        BIO_pop(membio1);

    testresult = 1;
 end:
    BIO_free(membio1);
    BIO_free(sslbio);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return testresult;
}