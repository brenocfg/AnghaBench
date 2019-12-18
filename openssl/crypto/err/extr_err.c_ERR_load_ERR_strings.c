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
 int /*<<< orphan*/  ERR_str_libraries ; 
 int /*<<< orphan*/  ERR_str_reasons ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_SYS_str_reasons () ; 
 int /*<<< orphan*/  do_err_strings_init ; 
 int /*<<< orphan*/  err_load_strings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_string_init ; 

int ERR_load_ERR_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (!RUN_ONCE(&err_string_init, do_err_strings_init))
        return 0;

    err_load_strings(ERR_str_libraries);
    err_load_strings(ERR_str_reasons);
    build_SYS_str_reasons();
#endif
    return 1;
}