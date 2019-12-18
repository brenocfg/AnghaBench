#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* readable; int /*<<< orphan*/  asn1; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int ASN1_TIME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_str_eq (char const*,char*) ; 
 int /*<<< orphan*/  TEST_strn_eq (char*,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_1__* x509_print_tests ; 

__attribute__((used)) static int test_x509_time_print(int idx)
{
    BIO *m;
    int ret = 0, rv;
    char *pp;
    const char *readable;

    if (!TEST_ptr(m = BIO_new(BIO_s_mem())))
        goto err;

    rv = ASN1_TIME_print(m, &x509_print_tests[idx].asn1);
    readable = x509_print_tests[idx].readable;

    if (rv == 0 && !TEST_str_eq(readable, "Bad time value")) {
        /* only if the test case intends to fail... */
        goto err;
    }
    if (!TEST_int_ne(rv = BIO_get_mem_data(m, &pp), 0)
        || !TEST_int_eq(rv, (int)strlen(readable))
        || !TEST_strn_eq(pp, readable, rv))
        goto err;

    ret = 1;
 err:
    BIO_free(m);
    return ret;
}