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
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_method () ; 
 int /*<<< orphan*/  get_sni_from_client_hello (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  host ; 

__attribute__((used)) static int client_setup_sni_before_state(void)
{
    SSL_CTX *ctx;
    SSL *con = NULL;
    BIO *rbio;
    BIO *wbio;
    char *hostname = NULL;
    int ret = 0;

    /* use TLS_method to blur 'side' */
    ctx = SSL_CTX_new(TLS_method());
    if (!TEST_ptr(ctx))
        goto end;

    con = SSL_new(ctx);
    if (!TEST_ptr(con))
        goto end;

    /* set SNI before 'client side' is set */
    SSL_set_tlsext_host_name(con, host);

    rbio = BIO_new(BIO_s_mem());
    wbio = BIO_new(BIO_s_mem());
    if (!TEST_ptr(rbio)|| !TEST_ptr(wbio)) {
        BIO_free(rbio);
        BIO_free(wbio);
        goto end;
    }

    SSL_set_bio(con, rbio, wbio);

    if (!TEST_int_le(SSL_connect(con), 0))
        /* This shouldn't succeed because we don't have a server! */
        goto end;
    if (!TEST_true(get_sni_from_client_hello(wbio, &hostname)))
        /* no SNI in client hello */
        goto end;
    if (!TEST_str_eq(hostname, host))
        /* incorrect SNI value */
        goto end;
    ret = 1;
end:
    OPENSSL_free(hostname);
    SSL_free(con);
    SSL_CTX_free(ctx);
    return ret;
}