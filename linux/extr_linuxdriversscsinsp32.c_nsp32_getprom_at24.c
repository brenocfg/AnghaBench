#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int limit_entry; } ;
typedef  TYPE_1__ nsp32_target ;
struct TYPE_8__ {TYPE_1__* target; void* resettime; } ;
typedef  TYPE_2__ nsp32_hw_data ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int NSP32_HOST_SCSIID ; 
 int TRUE ; 
 scalar_t__ ULTRA20M_MODE ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 void* nsp32_prom_read (TYPE_2__*,int) ; 
 int nsp32_search_period_entry (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ trans_mode ; 

__attribute__((used)) static int nsp32_getprom_at24(nsp32_hw_data *data)
{
	int           ret, i;
	int           auto_sync;
	nsp32_target *target;
	int           entry;

	/*
	 * Reset time which is designated by EEPROM.
	 *
	 * TODO: Not used yet.
	 */
	data->resettime = nsp32_prom_read(data, 0x12);

	/*
	 * HBA Synchronous Transfer Period
	 *
	 * Note: auto_sync = 0: auto, 1: manual.  Ninja SCSI HBA spec says
	 *	that if auto_sync is 0 (auto), and connected SCSI devices are
	 *	same or lower than 3, then transfer speed is set as ULTRA-20M.
	 *	On the contrary if connected SCSI devices are same or higher
	 *	than 4, then transfer speed is set as FAST-10M.
	 *
	 *	I break this rule. The number of connected SCSI devices are
	 *	only ignored. If auto_sync is 0 (auto), then transfer speed is
	 *	forced as ULTRA-20M.
	 */
	ret = nsp32_prom_read(data, 0x07);
	switch (ret) {
	case 0:
		auto_sync = TRUE;
		break;
	case 1:
		auto_sync = FALSE;
		break;
	default:
		nsp32_msg(KERN_WARNING,
			  "Unsupported Auto Sync mode. Fall back to manual mode.");
		auto_sync = TRUE;
	}

	if (trans_mode == ULTRA20M_MODE) {
		auto_sync = TRUE;
	}

	/*
	 * each device Synchronous Transfer Period
	 */
	for (i = 0; i < NSP32_HOST_SCSIID; i++) {
		target = &data->target[i];
		if (auto_sync == TRUE) {
			target->limit_entry = 0;   /* set as ULTRA20M */
		} else {
			ret   = nsp32_prom_read(data, i);
			entry = nsp32_search_period_entry(data, target, ret);
			if (entry < 0) {
				/* search failed... set maximum speed */
				entry = 0;
			}
			target->limit_entry = entry;
		}
	}

	return TRUE;
}