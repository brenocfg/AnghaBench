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
typedef  int u8 ;
struct fusb302_chip {int /*<<< orphan*/  toggling_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_STATUS1A ; 
#define  FUSB_REG_STATUS1A_TOGSS_AA 132 
 int FUSB_REG_STATUS1A_TOGSS_MASK ; 
 int FUSB_REG_STATUS1A_TOGSS_POS ; 
#define  FUSB_REG_STATUS1A_TOGSS_SNK1 131 
#define  FUSB_REG_STATUS1A_TOGSS_SNK2 130 
#define  FUSB_REG_STATUS1A_TOGSS_SRC1 129 
#define  FUSB_REG_STATUS1A_TOGSS_SRC2 128 
 int fusb302_handle_togdone_snk (struct fusb302_chip*,int) ; 
 int fusb302_handle_togdone_src (struct fusb302_chip*,int) ; 
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,...) ; 
 int /*<<< orphan*/  fusb302_set_toggling (struct fusb302_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_handle_togdone(struct fusb302_chip *chip)
{
	int ret = 0;
	u8 status1a;
	u8 togdone_result;

	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS1A, &status1a);
	if (ret < 0)
		return ret;
	togdone_result = (status1a >> FUSB_REG_STATUS1A_TOGSS_POS) &
			 FUSB_REG_STATUS1A_TOGSS_MASK;
	switch (togdone_result) {
	case FUSB_REG_STATUS1A_TOGSS_SNK1:
	case FUSB_REG_STATUS1A_TOGSS_SNK2:
		return fusb302_handle_togdone_snk(chip, togdone_result);
	case FUSB_REG_STATUS1A_TOGSS_SRC1:
	case FUSB_REG_STATUS1A_TOGSS_SRC2:
		return fusb302_handle_togdone_src(chip, togdone_result);
	case FUSB_REG_STATUS1A_TOGSS_AA:
		/* doesn't support */
		fusb302_log(chip, "AudioAccessory not supported");
		fusb302_set_toggling(chip, chip->toggling_mode);
		break;
	default:
		fusb302_log(chip, "TOGDONE with an invalid state: %d",
			    togdone_result);
		fusb302_set_toggling(chip, chip->toggling_mode);
		break;
	}
	return ret;
}