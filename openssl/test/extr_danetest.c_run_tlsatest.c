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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAfile ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  EVP_sha512 () ; 
 int /*<<< orphan*/  SSL_CTX_dane_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_dane_mtype_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  basedomain ; 
 int /*<<< orphan*/  test_tlsafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsafile ; 

__attribute__((used)) static int run_tlsatest(void)
{
    SSL_CTX *ctx = NULL;
    BIO *f = NULL;
    int ret = 0;

    if (!TEST_ptr(f = BIO_new_file(tlsafile, "r"))
            || !TEST_ptr(ctx = SSL_CTX_new(TLS_client_method()))
            || !TEST_int_gt(SSL_CTX_dane_enable(ctx), 0)
            || !TEST_true(SSL_CTX_load_verify_file(ctx, CAfile))
            || !TEST_int_gt(SSL_CTX_dane_mtype_set(ctx, EVP_sha512(), 2, 1),
                            0)
            || !TEST_int_gt(SSL_CTX_dane_mtype_set(ctx, EVP_sha256(), 1, 2),
                            0)
            || !TEST_int_gt(test_tlsafile(ctx, basedomain, f, tlsafile), 0))
        goto end;
    ret = 1;

end:
    BIO_free(f);
    SSL_CTX_free(ctx);

    return ret;
}