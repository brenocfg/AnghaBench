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
struct dlm_ctxt {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_complete_recovery_thread (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_complete_thread (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_destroy_dlm_worker (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_domain_events ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  dlm_unregister_domain_handlers (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_complete_dlm_shutdown(struct dlm_ctxt *dlm)
{
	dlm_unregister_domain_handlers(dlm);
	dlm_complete_thread(dlm);
	dlm_complete_recovery_thread(dlm);
	dlm_destroy_dlm_worker(dlm);

	/* We've left the domain. Now we can take ourselves out of the
	 * list and allow the kref stuff to help us free the
	 * memory. */
	spin_lock(&dlm_domain_lock);
	list_del_init(&dlm->list);
	spin_unlock(&dlm_domain_lock);

	/* Wake up anyone waiting for us to remove this domain */
	wake_up(&dlm_domain_events);
}