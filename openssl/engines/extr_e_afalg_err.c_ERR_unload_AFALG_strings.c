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
 int /*<<< orphan*/  AFALG_str_reasons ; 
 int /*<<< orphan*/  ERR_unload_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_loaded ; 
 int /*<<< orphan*/  lib_code ; 

__attribute__((used)) static void ERR_unload_AFALG_strings(void)
{
    if (error_loaded) {
#ifndef OPENSSL_NO_ERR
        ERR_unload_strings(lib_code, AFALG_str_reasons);
#endif
        error_loaded = 0;
    }
}