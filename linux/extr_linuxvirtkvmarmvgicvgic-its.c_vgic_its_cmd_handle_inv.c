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
struct its_ite {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int E_ITS_INV_UNMAPPED_INTERRUPT ; 
 struct its_ite* find_ite (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_get_deviceid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_get_id (int /*<<< orphan*/ *) ; 
 int update_lpi_config (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vgic_its_cmd_handle_inv(struct kvm *kvm, struct vgic_its *its,
				   u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	struct its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	if (!ite)
		return E_ITS_INV_UNMAPPED_INTERRUPT;

	return update_lpi_config(kvm, ite->irq, NULL, true);
}