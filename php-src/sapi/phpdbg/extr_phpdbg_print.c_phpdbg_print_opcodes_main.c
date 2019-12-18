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
typedef  int /*<<< orphan*/  zend_function ;

/* Variables and functions */
 scalar_t__ PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phpdbg_out (char*) ; 
 int /*<<< orphan*/  phpdbg_print_function_helper (int /*<<< orphan*/ *) ; 

void phpdbg_print_opcodes_main() {
	phpdbg_out("function name: (null)\n");
	phpdbg_print_function_helper((zend_function *) PHPDBG_G(ops));
}