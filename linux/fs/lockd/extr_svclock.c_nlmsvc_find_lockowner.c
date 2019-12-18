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
struct nlm_lockowner {int /*<<< orphan*/  list; int /*<<< orphan*/  host; int /*<<< orphan*/  pid; int /*<<< orphan*/  count; } ;
struct nlm_host {int /*<<< orphan*/  h_lock; int /*<<< orphan*/  h_lockowners; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nlm_lockowner* __nlmsvc_find_lockowner (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nlm_lockowner*) ; 
 struct nlm_lockowner* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_get_host (struct nlm_host*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nlm_lockowner *nlmsvc_find_lockowner(struct nlm_host *host, pid_t pid)
{
	struct nlm_lockowner *res, *new = NULL;

	spin_lock(&host->h_lock);
	res = __nlmsvc_find_lockowner(host, pid);

	if (res == NULL) {
		spin_unlock(&host->h_lock);
		new = kmalloc(sizeof(*res), GFP_KERNEL);
		spin_lock(&host->h_lock);
		res = __nlmsvc_find_lockowner(host, pid);
		if (res == NULL && new != NULL) {
			res = new;
			/* fs/locks.c will manage the refcount through lock_ops */
			refcount_set(&new->count, 1);
			new->pid = pid;
			new->host = nlm_get_host(host);
			list_add(&new->list, &host->h_lockowners);
			new = NULL;
		}
	}

	spin_unlock(&host->h_lock);
	kfree(new);
	return res;
}