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
struct ddebug_table {int /*<<< orphan*/  mod_name; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ddebug_table*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddebug_table_free(struct ddebug_table *dt)
{
	list_del_init(&dt->link);
	kfree_const(dt->mod_name);
	kfree(dt);
}