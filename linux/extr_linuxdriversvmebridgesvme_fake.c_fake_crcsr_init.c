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
typedef  int /*<<< orphan*/  u32 ;
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {int /*<<< orphan*/  crcsr_kernel; int /*<<< orphan*/  crcsr_bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VME_CRCSR_BUF_SIZE ; 
 int /*<<< orphan*/  fake_ptr_to_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fake_slot_get (struct vme_bridge*) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fake_crcsr_init(struct vme_bridge *fake_bridge)
{
	u32 vstat;
	struct fake_driver *bridge;

	bridge = fake_bridge->driver_priv;

	/* Allocate mem for CR/CSR image */
	bridge->crcsr_kernel = kzalloc(VME_CRCSR_BUF_SIZE, GFP_KERNEL);
	bridge->crcsr_bus = fake_ptr_to_pci(bridge->crcsr_kernel);
	if (!bridge->crcsr_kernel)
		return -ENOMEM;

	vstat = fake_slot_get(fake_bridge);

	pr_info("CR/CSR Offset: %d\n", vstat);

	return 0;
}