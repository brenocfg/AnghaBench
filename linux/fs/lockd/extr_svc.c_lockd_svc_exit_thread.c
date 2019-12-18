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

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockd_unregister_notifiers () ; 
 int /*<<< orphan*/  nlm_ntf_refcnt ; 
 int /*<<< orphan*/  nlmsvc_rqst ; 
 int /*<<< orphan*/  svc_exit_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lockd_svc_exit_thread(void)
{
	atomic_dec(&nlm_ntf_refcnt);
	lockd_unregister_notifiers();
	svc_exit_thread(nlmsvc_rqst);
}