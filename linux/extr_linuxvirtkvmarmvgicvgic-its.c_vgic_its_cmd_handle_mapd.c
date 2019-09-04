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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int /*<<< orphan*/  baser_device_table; } ;
struct kvm {int dummy; } ;
struct its_device {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int E_ITS_MAPD_DEVICE_OOR ; 
 int E_ITS_MAPD_ITTSIZE_OOR ; 
 int PTR_ERR_OR_ZERO (struct its_device*) ; 
 scalar_t__ VITS_TYPER_IDBITS ; 
 struct its_device* find_its_device (struct vgic_its*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_get_deviceid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_get_ittaddr (int /*<<< orphan*/ *) ; 
 scalar_t__ its_cmd_get_size (int /*<<< orphan*/ *) ; 
 int its_cmd_get_validbit (int /*<<< orphan*/ *) ; 
 struct its_device* vgic_its_alloc_device (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vgic_its_check_id (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_its_free_device (struct kvm*,struct its_device*) ; 

__attribute__((used)) static int vgic_its_cmd_handle_mapd(struct kvm *kvm, struct vgic_its *its,
				    u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	bool valid = its_cmd_get_validbit(its_cmd);
	u8 num_eventid_bits = its_cmd_get_size(its_cmd);
	gpa_t itt_addr = its_cmd_get_ittaddr(its_cmd);
	struct its_device *device;

	if (!vgic_its_check_id(its, its->baser_device_table, device_id, NULL))
		return E_ITS_MAPD_DEVICE_OOR;

	if (valid && num_eventid_bits > VITS_TYPER_IDBITS)
		return E_ITS_MAPD_ITTSIZE_OOR;

	device = find_its_device(its, device_id);

	/*
	 * The spec says that calling MAPD on an already mapped device
	 * invalidates all cached data for this device. We implement this
	 * by removing the mapping and re-establishing it.
	 */
	if (device)
		vgic_its_free_device(kvm, device);

	/*
	 * The spec does not say whether unmapping a not-mapped device
	 * is an error, so we are done in any case.
	 */
	if (!valid)
		return 0;

	device = vgic_its_alloc_device(its, device_id, itt_addr,
				       num_eventid_bits);

	return PTR_ERR_OR_ZERO(device);
}