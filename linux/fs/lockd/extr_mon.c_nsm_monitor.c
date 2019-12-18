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
struct nsm_res {scalar_t__ status; scalar_t__ state; } ;
struct nsm_handle {scalar_t__ sm_name; int sm_monitored; scalar_t__ sm_mon_name; scalar_t__ sm_addrbuf; } ;
struct nlm_host {struct nsm_handle* h_nsmhandle; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NSMPROC_MON ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 
 scalar_t__ nsm_local_state ; 
 int nsm_mon_unmon (struct nsm_handle*,int /*<<< orphan*/ ,struct nsm_res*,struct nlm_host const*) ; 
 scalar_t__ nsm_use_hostnames ; 
 int /*<<< orphan*/  pr_notice_ratelimited (char*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int nsm_monitor(const struct nlm_host *host)
{
	struct nsm_handle *nsm = host->h_nsmhandle;
	struct nsm_res	res;
	int		status;

	dprintk("lockd: nsm_monitor(%s)\n", nsm->sm_name);

	if (nsm->sm_monitored)
		return 0;

	/*
	 * Choose whether to record the caller_name or IP address of
	 * this peer in the local rpc.statd's database.
	 */
	nsm->sm_mon_name = nsm_use_hostnames ? nsm->sm_name : nsm->sm_addrbuf;

	status = nsm_mon_unmon(nsm, NSMPROC_MON, &res, host);
	if (unlikely(res.status != 0))
		status = -EIO;
	if (unlikely(status < 0)) {
		pr_notice_ratelimited("lockd: cannot monitor %s\n", nsm->sm_name);
		return status;
	}

	nsm->sm_monitored = 1;
	if (unlikely(nsm_local_state != res.state)) {
		nsm_local_state = res.state;
		dprintk("lockd: NSM state changed to %d\n", nsm_local_state);
	}
	return 0;
}