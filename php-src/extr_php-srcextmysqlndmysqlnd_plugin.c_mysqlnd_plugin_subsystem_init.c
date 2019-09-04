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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mysqlnd_registered_plugins ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mysqlnd_plugin_subsystem_init(void)
{
	zend_hash_init(&mysqlnd_registered_plugins, 4 /* initial hash size */, NULL /* hash_func */, NULL /* dtor */, TRUE /* pers */);
}