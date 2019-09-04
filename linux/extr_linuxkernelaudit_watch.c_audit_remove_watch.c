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
struct audit_watch {int /*<<< orphan*/ * parent; int /*<<< orphan*/  wlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_put_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_put_watch (struct audit_watch*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audit_remove_watch(struct audit_watch *watch)
{
	list_del(&watch->wlist);
	audit_put_parent(watch->parent);
	watch->parent = NULL;
	audit_put_watch(watch); /* match initial get */
}