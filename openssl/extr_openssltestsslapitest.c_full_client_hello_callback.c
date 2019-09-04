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
typedef  int /*<<< orphan*/  expected_ciphers ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int*) ; 
 size_t OSSL_NELEM (int const*) ; 
 int SSL_CLIENT_HELLO_ERROR ; 
 int SSL_CLIENT_HELLO_RETRY ; 
 int SSL_CLIENT_HELLO_SUCCESS ; 
 size_t SSL_client_hello_get0_ciphers (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  SSL_client_hello_get0_compression_methods (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  SSL_client_hello_get1_extensions_present (int /*<<< orphan*/ *,int**,size_t*) ; 
 int /*<<< orphan*/  TEST_int_eq (unsigned char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char const*,size_t,unsigned char const*,int) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (int*,int const*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int full_client_hello_callback(SSL *s, int *al, void *arg)
{
    int *ctr = arg;
    const unsigned char *p;
    int *exts;
    /* We only configure two ciphers, but the SCSV is added automatically. */
#ifdef OPENSSL_NO_EC
    const unsigned char expected_ciphers[] = {0x00, 0x9d, 0x00, 0xff};
#else
    const unsigned char expected_ciphers[] = {0x00, 0x9d, 0xc0,
                                              0x2c, 0x00, 0xff};
#endif
    const int expected_extensions[] = {
#ifndef OPENSSL_NO_EC
                                       11, 10,
#endif
                                       35, 22, 23, 13};
    size_t len;

    /* Make sure we can defer processing and get called back. */
    if ((*ctr)++ == 0)
        return SSL_CLIENT_HELLO_RETRY;

    len = SSL_client_hello_get0_ciphers(s, &p);
    if (!TEST_mem_eq(p, len, expected_ciphers, sizeof(expected_ciphers))
            || !TEST_size_t_eq(
                       SSL_client_hello_get0_compression_methods(s, &p), 1)
            || !TEST_int_eq(*p, 0))
        return SSL_CLIENT_HELLO_ERROR;
    if (!SSL_client_hello_get1_extensions_present(s, &exts, &len))
        return SSL_CLIENT_HELLO_ERROR;
    if (len != OSSL_NELEM(expected_extensions) ||
        memcmp(exts, expected_extensions, len * sizeof(*exts)) != 0) {
        printf("ClientHello callback expected extensions mismatch\n");
        OPENSSL_free(exts);
        return SSL_CLIENT_HELLO_ERROR;
    }
    OPENSSL_free(exts);
    return SSL_CLIENT_HELLO_SUCCESS;
}