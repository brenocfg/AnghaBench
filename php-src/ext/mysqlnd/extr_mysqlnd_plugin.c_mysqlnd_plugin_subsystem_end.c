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
 int /*<<< orphan*/  mysqlnd_plugin_end_apply_func ; 
 int /*<<< orphan*/  mysqlnd_registered_plugins ; 
 int /*<<< orphan*/  zend_hash_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

void
mysqlnd_plugin_subsystem_end(void)
{
	zend_hash_apply(&mysqlnd_registered_plugins, mysqlnd_plugin_end_apply_func);
	zend_hash_destroy(&mysqlnd_registered_plugins);
}