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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/ * OCSP_url_svcloc_new (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cert (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int test_ocsp_url_svcloc_new(void)
{
    static const char *  urls[] = {
        "www.openssl.org",
        "www.openssl.net",
        NULL
    };

    X509 *issuer = NULL;
    X509_EXTENSION * ext = NULL;
    int ret = 0;

    if (!TEST_true(get_cert(&issuer)))
        goto err;

    /*
     * Test calling this ocsp method to catch any memory leak
     */
    ext = OCSP_url_svcloc_new(X509_get_issuer_name(issuer), urls);
    if (!TEST_ptr(ext))
        goto err;

    X509_EXTENSION_free(ext);
    ret = 1;
err:
    X509_free(issuer);
    return ret;
}