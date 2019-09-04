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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_STORE_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  X509_load_cert_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* test_get_argument (int) ; 

__attribute__((used)) static int test_509_dup_cert(int n)
{
    int ret = 0;
    X509_STORE_CTX *sctx = NULL;
    X509_STORE *store = NULL;
    X509_LOOKUP *lookup = NULL;
    const char *cert_f = test_get_argument(n);

    if (TEST_ptr(store = X509_STORE_new())
        && TEST_ptr(lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file()))
        && TEST_true(X509_load_cert_file(lookup, cert_f, X509_FILETYPE_PEM))
        && TEST_true(X509_load_cert_file(lookup, cert_f, X509_FILETYPE_PEM)))
        ret = 1;

    X509_STORE_CTX_free(sctx);
    X509_STORE_free(store);
    return ret;
}