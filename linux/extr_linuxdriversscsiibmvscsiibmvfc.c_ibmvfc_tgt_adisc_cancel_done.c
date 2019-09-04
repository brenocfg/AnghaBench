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
struct ibmvfc_target {int /*<<< orphan*/  kref; } ;
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  abort_threads; } ;
struct ibmvfc_event {struct ibmvfc_target* tgt; struct ibmvfc_host* vhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_tgt_adisc_cancel_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_target *tgt = evt->tgt;

	tgt_dbg(tgt, "ADISC cancel complete\n");
	vhost->abort_threads--;
	ibmvfc_free_event(evt);
	kref_put(&tgt->kref, ibmvfc_release_tgt);
	wake_up(&vhost->work_wait_q);
}