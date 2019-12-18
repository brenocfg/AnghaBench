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
struct ipc_namespace {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ipc_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  mq_clear_sbinfo (struct ipc_namespace*) ; 
 int /*<<< orphan*/  mq_lock ; 
 int /*<<< orphan*/  mq_put_mnt (struct ipc_namespace*) ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void put_ipc_ns(struct ipc_namespace *ns)
{
	if (refcount_dec_and_lock(&ns->count, &mq_lock)) {
		mq_clear_sbinfo(ns);
		spin_unlock(&mq_lock);
		mq_put_mnt(ns);
		free_ipc_ns(ns);
	}
}