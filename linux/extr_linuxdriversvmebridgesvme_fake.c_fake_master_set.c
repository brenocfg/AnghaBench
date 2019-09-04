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
struct vme_master_resource {unsigned int number; int /*<<< orphan*/  lock; struct vme_bridge* parent; } ;
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {TYPE_1__* masters; } ;
struct TYPE_2__ {int enabled; unsigned long long vme_base; unsigned long long size; int aspace; int cycle; int dwidth; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VME_A16 139 
#define  VME_A24 138 
#define  VME_A32 137 
#define  VME_A64 136 
#define  VME_CRCSR 135 
#define  VME_D16 134 
#define  VME_D32 133 
#define  VME_D8 132 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fake_master_set(struct vme_master_resource *image, int enabled,
		unsigned long long vme_base, unsigned long long size,
		u32 aspace, u32 cycle, u32 dwidth)
{
	int retval = 0;
	unsigned int i;
	struct vme_bridge *fake_bridge;
	struct fake_driver *bridge;

	fake_bridge = image->parent;

	bridge = fake_bridge->driver_priv;

	/* Verify input data */
	if (vme_base & 0xFFFF) {
		pr_err("Invalid VME Window alignment\n");
		retval = -EINVAL;
		goto err_window;
	}

	if (size & 0xFFFF) {
		pr_err("Invalid size alignment\n");
		retval = -EINVAL;
		goto err_window;
	}

	if ((size == 0) && (enabled != 0)) {
		pr_err("Size must be non-zero for enabled windows\n");
		retval = -EINVAL;
		goto err_window;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D8:
	case VME_D16:
	case VME_D32:
		break;
	default:
		pr_err("Invalid data width\n");
		retval = -EINVAL;
		goto err_dwidth;
	}

	/* Setup address space */
	switch (aspace) {
	case VME_A16:
	case VME_A24:
	case VME_A32:
	case VME_A64:
	case VME_CRCSR:
	case VME_USER1:
	case VME_USER2:
	case VME_USER3:
	case VME_USER4:
		break;
	default:
		pr_err("Invalid address space\n");
		retval = -EINVAL;
		goto err_aspace;
	}

	spin_lock(&image->lock);

	i = image->number;

	bridge->masters[i].enabled = enabled;
	bridge->masters[i].vme_base = vme_base;
	bridge->masters[i].size = size;
	bridge->masters[i].aspace = aspace;
	bridge->masters[i].cycle = cycle;
	bridge->masters[i].dwidth = dwidth;

	spin_unlock(&image->lock);

	return 0;

err_aspace:
err_dwidth:
err_window:
	return retval;

}