#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ip_set {int /*<<< orphan*/  lock; TYPE_1__* variant; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct ip_set*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ip_set*) ; 

__attribute__((used)) static void
ip_set_flush_set(struct ip_set *set)
{
	pr_debug("set: %s\n",  set->name);

	spin_lock_bh(&set->lock);
	set->variant->flush(set);
	spin_unlock_bh(&set->lock);
}