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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_new () ; 
 int /*<<< orphan*/  X509_set_version (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static X509 *make_cert(void)
{
    X509 *crt = NULL;

    if (!TEST_ptr(crt = X509_new()))
        return NULL;
    if (!TEST_true(X509_set_version(crt, 2))) {
        X509_free(crt);
        return NULL;
    }
    return crt;
}