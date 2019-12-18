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
struct svc_rqst {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_freezable_should_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_exit_thread (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_process (struct svc_rqst*) ; 
 int svc_recv (struct svc_rqst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs4_callback_svc(void *vrqstp)
{
	int err;
	struct svc_rqst *rqstp = vrqstp;

	set_freezable();

	while (!kthread_freezable_should_stop(NULL)) {

		if (signal_pending(current))
			flush_signals(current);
		/*
		 * Listen for a request on the socket
		 */
		err = svc_recv(rqstp, MAX_SCHEDULE_TIMEOUT);
		if (err == -EAGAIN || err == -EINTR)
			continue;
		svc_process(rqstp);
	}
	svc_exit_thread(rqstp);
	module_put_and_exit(0);
	return 0;
}