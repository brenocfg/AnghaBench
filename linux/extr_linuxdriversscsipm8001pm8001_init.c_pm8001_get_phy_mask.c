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
struct pm8001_hba_info {TYPE_1__* pdev; } ;
struct TYPE_2__ {int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int) ; 

__attribute__((used)) static
void pm8001_get_phy_mask(struct pm8001_hba_info *pm8001_ha, int *phymask)
{
	switch (pm8001_ha->pdev->subsystem_device) {
	case 0x0070: /* H1280 - 8 external 0 internal */
	case 0x0072: /* H12F0 - 16 external 0 internal */
		*phymask = 0x0000;
		break;

	case 0x0071: /* H1208 - 0 external 8 internal */
	case 0x0073: /* H120F - 0 external 16 internal */
		*phymask = 0xFFFF;
		break;

	case 0x0080: /* H1244 - 4 external 4 internal */
		*phymask = 0x00F0;
		break;

	case 0x0081: /* H1248 - 4 external 8 internal */
		*phymask = 0x0FF0;
		break;

	case 0x0082: /* H1288 - 8 external 8 internal */
		*phymask = 0xFF00;
		break;

	default:
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("Unknown subsystem device=0x%.04x",
				pm8001_ha->pdev->subsystem_device));
	}
}