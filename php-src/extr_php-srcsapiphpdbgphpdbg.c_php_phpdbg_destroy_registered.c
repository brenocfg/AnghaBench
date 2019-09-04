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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  zend_function_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_phpdbg_destroy_registered(zval *data) /* {{{ */
{
	zend_function_dtor(data);
}