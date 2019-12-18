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

/* Variables and functions */
 scalar_t__ CRYPTO_mem_leaks_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  openssl_error_cb ; 
 int /*<<< orphan*/  set_test_title (int /*<<< orphan*/ *) ; 
 scalar_t__ should_report_leaks () ; 

int pulldown_test_framework(int ret)
{
    set_test_title(NULL);
#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    if (should_report_leaks()
        && CRYPTO_mem_leaks_cb(openssl_error_cb, NULL) <= 0)
        return EXIT_FAILURE;
#endif
    return ret;
}