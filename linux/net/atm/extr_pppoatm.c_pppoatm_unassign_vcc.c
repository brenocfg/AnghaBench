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
struct pppoatm_vcc {int /*<<< orphan*/  chan; int /*<<< orphan*/  wakeup_tasklet; int /*<<< orphan*/  old_release_cb; int /*<<< orphan*/  old_pop; int /*<<< orphan*/  old_push; } ;
struct atm_vcc {int /*<<< orphan*/ * user_back; int /*<<< orphan*/  release_cb; int /*<<< orphan*/  pop; int /*<<< orphan*/  push; } ;

/* Variables and functions */
 struct pppoatm_vcc* atmvcc_to_pvcc (struct atm_vcc*) ; 
 int /*<<< orphan*/  kfree (struct pppoatm_vcc*) ; 
 int /*<<< orphan*/  ppp_unregister_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppoatm_unassign_vcc(struct atm_vcc *atmvcc)
{
	struct pppoatm_vcc *pvcc;
	pvcc = atmvcc_to_pvcc(atmvcc);
	atmvcc->push = pvcc->old_push;
	atmvcc->pop = pvcc->old_pop;
	atmvcc->release_cb = pvcc->old_release_cb;
	tasklet_kill(&pvcc->wakeup_tasklet);
	ppp_unregister_channel(&pvcc->chan);
	atmvcc->user_back = NULL;
	kfree(pvcc);
}