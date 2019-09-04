#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ start; } ;
struct vme_master_resource {unsigned int number; int /*<<< orphan*/  lock; TYPE_1__ bus_resource; struct vme_bridge* parent; } ;
struct vme_bridge {int /*<<< orphan*/  parent; struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__* CA91CX42_LSI_BD ; 
 scalar_t__* CA91CX42_LSI_BS ; 
 scalar_t__* CA91CX42_LSI_CTL ; 
 unsigned int CA91CX42_LSI_CTL_EN ; 
 unsigned int CA91CX42_LSI_CTL_PGM_M ; 
 unsigned int CA91CX42_LSI_CTL_PGM_PGM ; 
 unsigned int CA91CX42_LSI_CTL_SUPER_M ; 
 unsigned int CA91CX42_LSI_CTL_SUPER_SUPR ; 
 unsigned int CA91CX42_LSI_CTL_VAS_A16 ; 
 unsigned int CA91CX42_LSI_CTL_VAS_A24 ; 
 unsigned int CA91CX42_LSI_CTL_VAS_A32 ; 
 unsigned int CA91CX42_LSI_CTL_VAS_CRCSR ; 
 unsigned int CA91CX42_LSI_CTL_VAS_M ; 
 unsigned int CA91CX42_LSI_CTL_VAS_USER1 ; 
 unsigned int CA91CX42_LSI_CTL_VAS_USER2 ; 
 unsigned int CA91CX42_LSI_CTL_VCT_BLT ; 
 unsigned int CA91CX42_LSI_CTL_VCT_M ; 
 unsigned int CA91CX42_LSI_CTL_VCT_MBLT ; 
 unsigned int CA91CX42_LSI_CTL_VDW_D16 ; 
 unsigned int CA91CX42_LSI_CTL_VDW_D32 ; 
 unsigned int CA91CX42_LSI_CTL_VDW_D64 ; 
 unsigned int CA91CX42_LSI_CTL_VDW_D8 ; 
 unsigned int CA91CX42_LSI_CTL_VDW_M ; 
 scalar_t__* CA91CX42_LSI_TO ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  VME_A16 140 
#define  VME_A24 139 
#define  VME_A32 138 
#define  VME_A64 137 
 int VME_BLT ; 
#define  VME_CRCSR 136 
#define  VME_D16 135 
#define  VME_D32 134 
#define  VME_D64 133 
#define  VME_D8 132 
 int VME_MBLT ; 
 int VME_PROG ; 
 int VME_SUPER ; 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int ca91cx42_alloc_resource (struct vme_master_resource*,unsigned long long) ; 
 int /*<<< orphan*/  ca91cx42_free_resource (struct vme_master_resource*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ca91cx42_master_set(struct vme_master_resource *image, int enabled,
	unsigned long long vme_base, unsigned long long size, u32 aspace,
	u32 cycle, u32 dwidth)
{
	int retval = 0;
	unsigned int i, granularity = 0;
	unsigned int temp_ctl = 0;
	unsigned long long pci_bound, vme_offset, pci_base;
	struct vme_bridge *ca91cx42_bridge;
	struct ca91cx42_driver *bridge;

	ca91cx42_bridge = image->parent;

	bridge = ca91cx42_bridge->driver_priv;

	i = image->number;

	if ((i == 0) || (i == 4))
		granularity = 0x1000;
	else
		granularity = 0x10000;

	/* Verify input data */
	if (vme_base & (granularity - 1)) {
		dev_err(ca91cx42_bridge->parent, "Invalid VME Window "
			"alignment\n");
		retval = -EINVAL;
		goto err_window;
	}
	if (size & (granularity - 1)) {
		dev_err(ca91cx42_bridge->parent, "Invalid VME Window "
			"alignment\n");
		retval = -EINVAL;
		goto err_window;
	}

	spin_lock(&image->lock);

	/*
	 * Let's allocate the resource here rather than further up the stack as
	 * it avoids pushing loads of bus dependent stuff up the stack
	 */
	retval = ca91cx42_alloc_resource(image, size);
	if (retval) {
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Unable to allocate memory "
			"for resource name\n");
		retval = -ENOMEM;
		goto err_res;
	}

	pci_base = (unsigned long long)image->bus_resource.start;

	/*
	 * Bound address is a valid address for the window, adjust
	 * according to window granularity.
	 */
	pci_bound = pci_base + size;
	vme_offset = vme_base - pci_base;

	/* Disable while we are mucking around */
	temp_ctl = ioread32(bridge->base + CA91CX42_LSI_CTL[i]);
	temp_ctl &= ~CA91CX42_LSI_CTL_EN;
	iowrite32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	/* Setup cycle types */
	temp_ctl &= ~CA91CX42_LSI_CTL_VCT_M;
	if (cycle & VME_BLT)
		temp_ctl |= CA91CX42_LSI_CTL_VCT_BLT;
	if (cycle & VME_MBLT)
		temp_ctl |= CA91CX42_LSI_CTL_VCT_MBLT;

	/* Setup data width */
	temp_ctl &= ~CA91CX42_LSI_CTL_VDW_M;
	switch (dwidth) {
	case VME_D8:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D8;
		break;
	case VME_D16:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D16;
		break;
	case VME_D32:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D32;
		break;
	case VME_D64:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D64;
		break;
	default:
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Invalid data width\n");
		retval = -EINVAL;
		goto err_dwidth;
		break;
	}

	/* Setup address space */
	temp_ctl &= ~CA91CX42_LSI_CTL_VAS_M;
	switch (aspace) {
	case VME_A16:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A16;
		break;
	case VME_A24:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A24;
		break;
	case VME_A32:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A32;
		break;
	case VME_CRCSR:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_CRCSR;
		break;
	case VME_USER1:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_USER1;
		break;
	case VME_USER2:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_USER2;
		break;
	case VME_A64:
	case VME_USER3:
	case VME_USER4:
	default:
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Invalid address space\n");
		retval = -EINVAL;
		goto err_aspace;
		break;
	}

	temp_ctl &= ~(CA91CX42_LSI_CTL_PGM_M | CA91CX42_LSI_CTL_SUPER_M);
	if (cycle & VME_SUPER)
		temp_ctl |= CA91CX42_LSI_CTL_SUPER_SUPR;
	if (cycle & VME_PROG)
		temp_ctl |= CA91CX42_LSI_CTL_PGM_PGM;

	/* Setup mapping */
	iowrite32(pci_base, bridge->base + CA91CX42_LSI_BS[i]);
	iowrite32(pci_bound, bridge->base + CA91CX42_LSI_BD[i]);
	iowrite32(vme_offset, bridge->base + CA91CX42_LSI_TO[i]);

	/* Write ctl reg without enable */
	iowrite32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	if (enabled)
		temp_ctl |= CA91CX42_LSI_CTL_EN;

	iowrite32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	spin_unlock(&image->lock);
	return 0;

err_aspace:
err_dwidth:
	ca91cx42_free_resource(image);
err_res:
err_window:
	return retval;
}