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
struct kvm_vcpu {int dummy; } ;
struct kvm {int dummy; } ;
struct its_ite {int /*<<< orphan*/  irq; struct its_collection* collection; } ;
struct its_collection {int /*<<< orphan*/  target_addr; } ;

/* Variables and functions */
 int E_ITS_MOVI_UNMAPPED_COLLECTION ; 
 int E_ITS_MOVI_UNMAPPED_INTERRUPT ; 
 struct its_collection* find_collection (struct vgic_its*,int /*<<< orphan*/ ) ; 
 struct its_ite* find_ite (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_get_collection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_get_deviceid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_is_collection_mapped (struct its_collection*) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 int update_affinity (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_its_invalidate_cache (struct kvm*) ; 

__attribute__((used)) static int vgic_its_cmd_handle_movi(struct kvm *kvm, struct vgic_its *its,
				    u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	u32 coll_id = its_cmd_get_collection(its_cmd);
	struct kvm_vcpu *vcpu;
	struct its_ite *ite;
	struct its_collection *collection;

	ite = find_ite(its, device_id, event_id);
	if (!ite)
		return E_ITS_MOVI_UNMAPPED_INTERRUPT;

	if (!its_is_collection_mapped(ite->collection))
		return E_ITS_MOVI_UNMAPPED_COLLECTION;

	collection = find_collection(its, coll_id);
	if (!its_is_collection_mapped(collection))
		return E_ITS_MOVI_UNMAPPED_COLLECTION;

	ite->collection = collection;
	vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	vgic_its_invalidate_cache(kvm);

	return update_affinity(ite->irq, vcpu);
}