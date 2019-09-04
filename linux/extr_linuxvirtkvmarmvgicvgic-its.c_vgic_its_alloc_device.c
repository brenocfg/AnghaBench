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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int /*<<< orphan*/  device_list; } ;
struct its_device {int /*<<< orphan*/  dev_list; int /*<<< orphan*/  itt_head; int /*<<< orphan*/  num_eventid_bits; int /*<<< orphan*/  itt_addr; int /*<<< orphan*/  device_id; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct its_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct its_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct its_device *vgic_its_alloc_device(struct vgic_its *its,
						u32 device_id, gpa_t itt_addr,
						u8 num_eventid_bits)
{
	struct its_device *device;

	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device)
		return ERR_PTR(-ENOMEM);

	device->device_id = device_id;
	device->itt_addr = itt_addr;
	device->num_eventid_bits = num_eventid_bits;
	INIT_LIST_HEAD(&device->itt_head);

	list_add_tail(&device->dev_list, &its->device_list);
	return device;
}