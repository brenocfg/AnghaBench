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
struct nlm_host {int h_server; int /*<<< orphan*/  h_reclaim; int /*<<< orphan*/  h_granted; int /*<<< orphan*/  h_lockowners; int /*<<< orphan*/  h_count; int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_destroy_host_locked (struct nlm_host*) ; 
 int /*<<< orphan*/  nlm_host_mutex ; 
 scalar_t__ refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nlmclnt_release_host(struct nlm_host *host)
{
	if (host == NULL)
		return;

	dprintk("lockd: release client host %s\n", host->h_name);

	WARN_ON_ONCE(host->h_server);

	if (refcount_dec_and_mutex_lock(&host->h_count, &nlm_host_mutex)) {
		WARN_ON_ONCE(!list_empty(&host->h_lockowners));
		WARN_ON_ONCE(!list_empty(&host->h_granted));
		WARN_ON_ONCE(!list_empty(&host->h_reclaim));

		nlm_destroy_host_locked(host);
		mutex_unlock(&nlm_host_mutex);
	}
}