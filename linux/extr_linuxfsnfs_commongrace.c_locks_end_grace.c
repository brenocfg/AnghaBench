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
struct lock_manager {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  grace_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
locks_end_grace(struct lock_manager *lm)
{
	spin_lock(&grace_lock);
	list_del_init(&lm->list);
	spin_unlock(&grace_lock);
}