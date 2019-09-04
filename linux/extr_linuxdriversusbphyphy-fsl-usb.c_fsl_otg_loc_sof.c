#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct otg_fsm {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dr_mem_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  portsc; } ;

/* Variables and functions */
 int PORTSC_PORT_FORCE_RESUME ; 
 int PORTSC_PORT_SUSPEND ; 
 int PORTSC_W1C_BITS ; 
 TYPE_2__* fsl_otg_dev ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 

void fsl_otg_loc_sof(struct otg_fsm *fsm, int on)
{
	u32 tmp;

	tmp = fsl_readl(&fsl_otg_dev->dr_mem_map->portsc) & ~PORTSC_W1C_BITS;
	if (on)
		tmp |= PORTSC_PORT_FORCE_RESUME;
	else
		tmp |= PORTSC_PORT_SUSPEND;

	fsl_writel(tmp, &fsl_otg_dev->dr_mem_map->portsc);

}