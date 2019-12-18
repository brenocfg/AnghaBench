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
struct audit_watch {int /*<<< orphan*/  rules; struct audit_parent* parent; } ;
struct audit_parent {int /*<<< orphan*/  mark; int /*<<< orphan*/  watches; } ;
struct audit_krule {int /*<<< orphan*/  rlist; struct audit_watch* watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_get_parent (struct audit_parent*) ; 
 int /*<<< orphan*/  audit_put_parent (struct audit_parent*) ; 
 int /*<<< orphan*/  audit_remove_watch (struct audit_watch*) ; 
 int /*<<< orphan*/  audit_watch_group ; 
 int /*<<< orphan*/  fsnotify_destroy_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

void audit_remove_watch_rule(struct audit_krule *krule)
{
	struct audit_watch *watch = krule->watch;
	struct audit_parent *parent = watch->parent;

	list_del(&krule->rlist);

	if (list_empty(&watch->rules)) {
		/*
		 * audit_remove_watch() drops our reference to 'parent' which
		 * can get freed. Grab our own reference to be safe.
		 */
		audit_get_parent(parent);
		audit_remove_watch(watch);
		if (list_empty(&parent->watches))
			fsnotify_destroy_mark(&parent->mark, audit_watch_group);
		audit_put_parent(parent);
	}
}