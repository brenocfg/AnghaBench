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
struct nlm_lockowner {TYPE_1__* host; int /*<<< orphan*/  list; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nlm_lockowner*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_release_host (TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nlmsvc_put_lockowner(struct nlm_lockowner *lockowner)
{
	if (!refcount_dec_and_lock(&lockowner->count, &lockowner->host->h_lock))
		return;
	list_del(&lockowner->list);
	spin_unlock(&lockowner->host->h_lock);
	nlmsvc_release_host(lockowner->host);
	kfree(lockowner);
}