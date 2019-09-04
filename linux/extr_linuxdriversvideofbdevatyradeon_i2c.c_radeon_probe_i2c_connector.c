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
typedef  int u8 ;
struct radeonfb_info {scalar_t__ is_mobility; TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVDS_GEN_CNTL ; 
 int LVDS_ON ; 
 int MT_CRT ; 
 int MT_DFP ; 
 int MT_LCD ; 
 int MT_NONE ; 
 int* fb_ddc_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int radeon_probe_i2c_connector(struct radeonfb_info *rinfo, int conn,
			       u8 **out_edid)
{
	u8 *edid;

	edid = fb_ddc_read(&rinfo->i2c[conn-1].adapter);

	if (out_edid)
		*out_edid = edid;
	if (!edid) {
		pr_debug("radeonfb: I2C (port %d) ... not found\n", conn);
		return MT_NONE;
	}
	if (edid[0x14] & 0x80) {
		/* Fix detection using BIOS tables */
		if (rinfo->is_mobility /*&& conn == ddc_dvi*/ &&
		    (INREG(LVDS_GEN_CNTL) & LVDS_ON)) {
			pr_debug("radeonfb: I2C (port %d) ... found LVDS panel\n", conn);
			return MT_LCD;
		} else {
			pr_debug("radeonfb: I2C (port %d) ... found TMDS panel\n", conn);
			return MT_DFP;
		}
	}
	pr_debug("radeonfb: I2C (port %d) ... found CRT display\n", conn);
	return MT_CRT;
}