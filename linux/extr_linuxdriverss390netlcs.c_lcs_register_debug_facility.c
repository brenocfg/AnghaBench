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
 int ENOMEM ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 int /*<<< orphan*/ * debug_register (char*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lcs_dbf_setup ; 
 int /*<<< orphan*/ * lcs_dbf_trace ; 
 int /*<<< orphan*/  lcs_unregister_debug_facility () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
lcs_register_debug_facility(void)
{
	lcs_dbf_setup = debug_register("lcs_setup", 2, 1, 8);
	lcs_dbf_trace = debug_register("lcs_trace", 4, 1, 8);
	if (lcs_dbf_setup == NULL || lcs_dbf_trace == NULL) {
		pr_err("Not enough memory for debug facility.\n");
		lcs_unregister_debug_facility();
		return -ENOMEM;
	}
	debug_register_view(lcs_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(lcs_dbf_setup, 2);
	debug_register_view(lcs_dbf_trace, &debug_hex_ascii_view);
	debug_set_level(lcs_dbf_trace, 2);
	return 0;
}