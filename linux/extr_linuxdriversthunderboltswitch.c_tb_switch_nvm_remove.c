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
struct tb_switch_nvm {int /*<<< orphan*/  buf; int /*<<< orphan*/  id; scalar_t__ active; scalar_t__ non_active; int /*<<< orphan*/  authenticating; } ;
struct tb_switch {struct tb_switch_nvm* nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tb_switch_nvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_clear_auth_status (struct tb_switch*) ; 
 int /*<<< orphan*/  nvm_ida ; 
 int /*<<< orphan*/  nvmem_unregister (scalar_t__) ; 
 int /*<<< orphan*/  switch_lock ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb_switch_nvm_remove(struct tb_switch *sw)
{
	struct tb_switch_nvm *nvm;

	mutex_lock(&switch_lock);
	nvm = sw->nvm;
	sw->nvm = NULL;
	mutex_unlock(&switch_lock);

	if (!nvm)
		return;

	/* Remove authentication status in case the switch is unplugged */
	if (!nvm->authenticating)
		nvm_clear_auth_status(sw);

	nvmem_unregister(nvm->non_active);
	if (nvm->active)
		nvmem_unregister(nvm->active);
	ida_simple_remove(&nvm_ida, nvm->id);
	vfree(nvm->buf);
	kfree(nvm);
}