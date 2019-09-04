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
typedef  int /*<<< orphan*/  llist_apply_func_t ;

/* Variables and functions */
 scalar_t__ zend_extension_shutdown ; 
 int /*<<< orphan*/  zend_extensions ; 
 int /*<<< orphan*/  zend_llist_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_llist_destroy (int /*<<< orphan*/ *) ; 

void zend_shutdown_extensions(void)
{
	zend_llist_apply(&zend_extensions, (llist_apply_func_t) zend_extension_shutdown);
	zend_llist_destroy(&zend_extensions);
}