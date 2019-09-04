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
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_err_strings_init ; 
 int /*<<< orphan*/  err_string_init ; 
 int /*<<< orphan*/  err_string_lock ; 
 int /*<<< orphan*/  int_err_library_number ; 

int ERR_get_next_error_library(void)
{
    int ret;

    if (!RUN_ONCE(&err_string_init, do_err_strings_init))
        return 0;

    CRYPTO_THREAD_write_lock(err_string_lock);
    ret = int_err_library_number++;
    CRYPTO_THREAD_unlock(err_string_lock);
    return ret;
}