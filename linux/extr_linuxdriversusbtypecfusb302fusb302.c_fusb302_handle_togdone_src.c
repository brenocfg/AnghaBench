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
typedef  scalar_t__ u8 ;
struct fusb302_chip {size_t src_current_status; int cc1; int cc2; int intr_comp_chng; int /*<<< orphan*/  tcpm_port; int /*<<< orphan*/  toggling_mode; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_MASK ; 
 int /*<<< orphan*/  FUSB_REG_MASK_COMP_CHNG ; 
 int /*<<< orphan*/  FUSB_REG_MEASURE ; 
 int /*<<< orphan*/  FUSB_REG_STATUS0 ; 
 scalar_t__ FUSB_REG_STATUS0_COMP ; 
 scalar_t__ FUSB_REG_STATUS1A_TOGSS_SRC1 ; 
 int /*<<< orphan*/  TOGGLINE_MODE_OFF ; 
 int TYPEC_CC_OPEN ; 
 int TYPEC_CC_RD ; 
 int TYPEC_POLARITY_CC1 ; 
 int TYPEC_POLARITY_CC2 ; 
 int* cc_polarity_name ; 
 int fusb302_i2c_clear_bits (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,...) ; 
 int fusb302_set_cc_polarity (struct fusb302_chip*,int) ; 
 int fusb302_set_cc_pull (struct fusb302_chip*,int,int) ; 
 int fusb302_set_toggling (struct fusb302_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__* ra_mda_value ; 
 scalar_t__* rd_mda_value ; 
 int /*<<< orphan*/  tcpm_cc_change (int /*<<< orphan*/ ) ; 
 int* typec_cc_status_name ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int fusb302_handle_togdone_src(struct fusb302_chip *chip,
				      u8 togdone_result)
{
	/*
	 * - set polarity (measure cc, vconn, tx)
	 * - set pull_up, pull_down
	 * - set cc1, cc2, and update to tcpm_port
	 * - set I_COMP interrupt on
	 */
	int ret = 0;
	u8 status0;
	u8 ra_mda = ra_mda_value[chip->src_current_status];
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	bool ra_comp, rd_comp;
	enum typec_cc_polarity cc_polarity;
	enum typec_cc_status cc_status_active, cc1, cc2;

	/* set pull_up, pull_down */
	ret = fusb302_set_cc_pull(chip, true, false);
	if (ret < 0) {
		fusb302_log(chip, "cannot set cc to pull up, ret=%d", ret);
		return ret;
	}
	/* set polarity */
	cc_polarity = (togdone_result == FUSB_REG_STATUS1A_TOGSS_SRC1) ?
		      TYPEC_POLARITY_CC1 : TYPEC_POLARITY_CC2;
	ret = fusb302_set_cc_polarity(chip, cc_polarity);
	if (ret < 0) {
		fusb302_log(chip, "cannot set cc polarity %s, ret=%d",
			    cc_polarity_name[cc_polarity], ret);
		return ret;
	}
	/* fusb302_set_cc_polarity() has set the correct measure block */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
	if (ret < 0)
		return ret;
	usleep_range(50, 100);
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret < 0)
		return ret;
	rd_comp = !!(status0 & FUSB_REG_STATUS0_COMP);
	if (!rd_comp) {
		ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, ra_mda);
		if (ret < 0)
			return ret;
		usleep_range(50, 100);
		ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
		if (ret < 0)
			return ret;
		ra_comp = !!(status0 & FUSB_REG_STATUS0_COMP);
	}
	if (rd_comp)
		cc_status_active = TYPEC_CC_OPEN;
	else if (ra_comp)
		cc_status_active = TYPEC_CC_RD;
	else
		/* Ra is not supported, report as Open */
		cc_status_active = TYPEC_CC_OPEN;
	/* restart toggling if the cc status on the active line is OPEN */
	if (cc_status_active == TYPEC_CC_OPEN) {
		fusb302_log(chip, "restart toggling as CC_OPEN detected");
		ret = fusb302_set_toggling(chip, chip->toggling_mode);
		return ret;
	}
	/* update tcpm with the new cc value */
	cc1 = (cc_polarity == TYPEC_POLARITY_CC1) ?
	      cc_status_active : TYPEC_CC_OPEN;
	cc2 = (cc_polarity == TYPEC_POLARITY_CC2) ?
	      cc_status_active : TYPEC_CC_OPEN;
	if ((chip->cc1 != cc1) || (chip->cc2 != cc2)) {
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_port);
	}
	/* turn off toggling */
	ret = fusb302_set_toggling(chip, TOGGLINE_MODE_OFF);
	if (ret < 0) {
		fusb302_log(chip,
			    "cannot set toggling mode off, ret=%d", ret);
		return ret;
	}
	/* set MDAC to Rd threshold, and unmask I_COMP for unplug detection */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
	if (ret < 0)
		return ret;
	/* unmask comp_chng interrupt */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASK,
				     FUSB_REG_MASK_COMP_CHNG);
	if (ret < 0) {
		fusb302_log(chip,
			    "cannot unmask bc_lcl interrupt, ret=%d", ret);
		return ret;
	}
	chip->intr_comp_chng = true;
	fusb302_log(chip, "detected cc1=%s, cc2=%s",
		    typec_cc_status_name[cc1],
		    typec_cc_status_name[cc2]);

	return ret;
}