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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int dummy; } ;
struct kvm {int dummy; } ;
struct its_ite {scalar_t__ collection; } ;

/* Variables and functions */
 int E_ITS_DISCARD_UNMAPPED_INTERRUPT ; 
 struct its_ite* find_ite (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_get_deviceid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_free_ite (struct kvm*,struct its_ite*) ; 
 int /*<<< orphan*/  vgic_its_invalidate_cache (struct kvm*) ; 

__attribute__((used)) static int vgic_its_cmd_handle_discard(struct kvm *kvm, struct vgic_its *its,
				       u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	struct its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	if (ite && ite->collection) {
		/*
		 * Though the spec talks about removing the pending state, we
		 * don't bother here since we clear the ITTE anyway and the
		 * pending state is a property of the ITTE struct.
		 */
		vgic_its_invalidate_cache(kvm);

		its_free_ite(kvm, ite);
		return 0;
	}

	return E_ITS_DISCARD_UNMAPPED_INTERRUPT;
}