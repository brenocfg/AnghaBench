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
typedef  int /*<<< orphan*/  PHPDBG_G ;

/* Variables and functions */
 int /*<<< orphan*/  phpdbg_init_compile_file ; 
 int /*<<< orphan*/  zend_compile_file ; 

void phpdbg_list_update(void) {
	PHPDBG_G(init_compile_file) = zend_compile_file;
	zend_compile_file = phpdbg_init_compile_file;
}