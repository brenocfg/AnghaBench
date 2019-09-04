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
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct pm8001_hba_info {TYPE_1__* phy; int /*<<< orphan*/  sas_addr; TYPE_2__* chip; } ;
struct TYPE_4__ {size_t n_phy; } ;
struct TYPE_3__ {int dev_sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm8001_init_sas_add(struct pm8001_hba_info *pm8001_ha)
{
	u8 i, j;
	u8 sas_add[8];
#ifdef PM8001_READ_VPD
	/* For new SPC controllers WWN is stored in flash vpd
	*  For SPC/SPCve controllers WWN is stored in EEPROM
	*  For Older SPC WWN is stored in NVMD
	*/
	DECLARE_COMPLETION_ONSTACK(completion);
	struct pm8001_ioctl_payload payload;
	u16 deviceid;
	int rc;

	pci_read_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	pm8001_ha->nvmd_completion = &completion;

	if (pm8001_ha->chip_id == chip_8001) {
		if (deviceid == 0x8081 || deviceid == 0x0042) {
			payload.minor_function = 4;
			payload.length = 4096;
		} else {
			payload.minor_function = 0;
			payload.length = 128;
		}
	} else if ((pm8001_ha->chip_id == chip_8070 ||
			pm8001_ha->chip_id == chip_8072) &&
			pm8001_ha->pdev->subsystem_vendor == PCI_VENDOR_ID_ATTO) {
		payload.minor_function = 4;
		payload.length = 4096;
	} else {
		payload.minor_function = 1;
		payload.length = 4096;
	}
	payload.offset = 0;
	payload.func_specific = kzalloc(payload.length, GFP_KERNEL);
	if (!payload.func_specific) {
		PM8001_INIT_DBG(pm8001_ha, pm8001_printk("mem alloc fail\n"));
		return;
	}
	rc = PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload);
	if (rc) {
		kfree(payload.func_specific);
		PM8001_INIT_DBG(pm8001_ha, pm8001_printk("nvmd failed\n"));
		return;
	}
	wait_for_completion(&completion);

	for (i = 0, j = 0; i <= 7; i++, j++) {
		if (pm8001_ha->chip_id == chip_8001) {
			if (deviceid == 0x8081)
				pm8001_ha->sas_addr[j] =
					payload.func_specific[0x704 + i];
			else if (deviceid == 0x0042)
				pm8001_ha->sas_addr[j] =
					payload.func_specific[0x010 + i];
		} else if ((pm8001_ha->chip_id == chip_8070 ||
				pm8001_ha->chip_id == chip_8072) &&
				pm8001_ha->pdev->subsystem_vendor == PCI_VENDOR_ID_ATTO) {
			pm8001_ha->sas_addr[j] =
					payload.func_specific[0x010 + i];
		} else
			pm8001_ha->sas_addr[j] =
					payload.func_specific[0x804 + i];
	}
	memcpy(sas_add, pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	for (i = 0; i < pm8001_ha->chip->n_phy; i++) {
		if (i && ((i % 4) == 0))
			sas_add[7] = sas_add[7] + 4;
		memcpy(&pm8001_ha->phy[i].dev_sas_addr,
			sas_add, SAS_ADDR_SIZE);
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("phy %d sas_addr = %016llx\n", i,
			pm8001_ha->phy[i].dev_sas_addr));
	}
	kfree(payload.func_specific);
#else
	for (i = 0; i < pm8001_ha->chip->n_phy; i++) {
		pm8001_ha->phy[i].dev_sas_addr = 0x50010c600047f9d0ULL;
		pm8001_ha->phy[i].dev_sas_addr =
			cpu_to_be64((u64)
				(*(u64 *)&pm8001_ha->phy[i].dev_sas_addr));
	}
	memcpy(pm8001_ha->sas_addr, &pm8001_ha->phy[0].dev_sas_addr,
		SAS_ADDR_SIZE);
#endif
}