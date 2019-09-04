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
union pa_cfg_sfr {int bias_current_trim; int buffer_capacitor_trim; int boost; int paib; } ;
typedef  int u8 ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ CA8210_MAC_MPW ; 
 int /*<<< orphan*/  CA8210_SFR_PACFG ; 
 int /*<<< orphan*/  CA8210_SFR_PACFGIB ; 
 int tdme_setsfr_request_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static u8 tdme_settxpower(u8 txp, void *device_ref)
{
	u8 status;
	s8 txp_val;
	u8 txp_ext;
	union pa_cfg_sfr pa_cfg_val;

	/* extend from 6 to 8 bit */
	txp_ext = 0x3F & txp;
	if (txp_ext & 0x20)
		txp_ext += 0xC0;
	txp_val = (s8)txp_ext;

	if (CA8210_MAC_MPW) {
		if (txp_val > 0) {
			/* 8 dBm: ptrim = 5, itrim = +3 => +4 dBm */
			pa_cfg_val.bias_current_trim     = 3;
			pa_cfg_val.buffer_capacitor_trim = 5;
			pa_cfg_val.boost                 = 1;
		} else {
			/* 0 dBm: ptrim = 7, itrim = +3 => -6 dBm */
			pa_cfg_val.bias_current_trim     = 3;
			pa_cfg_val.buffer_capacitor_trim = 7;
			pa_cfg_val.boost                 = 0;
		}
		/* write PACFG */
		status = tdme_setsfr_request_sync(
			0,
			CA8210_SFR_PACFG,
			pa_cfg_val.paib,
			device_ref
		);
	} else {
		/* Look-Up Table for Setting Current and Frequency Trim values
		 * for desired Output Power
		 */
		if (txp_val > 8) {
			pa_cfg_val.paib = 0x3F;
		} else if (txp_val == 8) {
			pa_cfg_val.paib = 0x32;
		} else if (txp_val == 7) {
			pa_cfg_val.paib = 0x22;
		} else if (txp_val == 6) {
			pa_cfg_val.paib = 0x18;
		} else if (txp_val == 5) {
			pa_cfg_val.paib = 0x10;
		} else if (txp_val == 4) {
			pa_cfg_val.paib = 0x0C;
		} else if (txp_val == 3) {
			pa_cfg_val.paib = 0x08;
		} else if (txp_val == 2) {
			pa_cfg_val.paib = 0x05;
		} else if (txp_val == 1) {
			pa_cfg_val.paib = 0x03;
		} else if (txp_val == 0) {
			pa_cfg_val.paib = 0x01;
		} else { /* < 0 */
			pa_cfg_val.paib = 0x00;
		}
		/* write PACFGIB */
		status = tdme_setsfr_request_sync(
			0,
			CA8210_SFR_PACFGIB,
			pa_cfg_val.paib,
			device_ref
		);
	}

	return status;
}