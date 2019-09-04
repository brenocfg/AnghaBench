#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* fixed_res; TYPE_2__* card; TYPE_1__* dma_adb; } ;
typedef  TYPE_3__ vortex_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int* resources; } ;

/* Variables and functions */
 char EINVAL ; 
 char ENOMEM ; 
 int NR_ADB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int* resnum ; 

__attribute__((used)) static char
vortex_adb_checkinout(vortex_t * vortex, int resmap[], int out, int restype)
{
	int i, qty = resnum[restype], resinuse = 0;

	if (out) {
		/* Gather used resources by all streams. */
		for (i = 0; i < NR_ADB; i++) {
			resinuse |= vortex->dma_adb[i].resources[restype];
		}
		resinuse |= vortex->fixed_res[restype];
		/* Find and take free resource. */
		for (i = 0; i < qty; i++) {
			if ((resinuse & (1 << i)) == 0) {
				if (resmap != NULL)
					resmap[restype] |= (1 << i);
				else
					vortex->dma_adb[i].resources[restype] |= (1 << i);
				/*
				pr_debug(
				       "vortex: ResManager: type %d out %d\n",
				       restype, i);
				*/
				return i;
			}
		}
	} else {
		if (resmap == NULL)
			return -EINVAL;
		/* Checkin first resource of type restype. */
		for (i = 0; i < qty; i++) {
			if (resmap[restype] & (1 << i)) {
				resmap[restype] &= ~(1 << i);
				/*
				pr_debug(
				       "vortex: ResManager: type %d in %d\n",
				       restype, i);
				*/
				return i;
			}
		}
	}
	dev_err(vortex->card->dev,
		"FATAL: ResManager: resource type %d exhausted.\n",
		restype);
	return -ENOMEM;
}