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
struct kset {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_init_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void kset_init(struct kset *k)
{
	kobject_init_internal(&k->kobj);
	INIT_LIST_HEAD(&k->list);
	spin_lock_init(&k->list_lock);
}