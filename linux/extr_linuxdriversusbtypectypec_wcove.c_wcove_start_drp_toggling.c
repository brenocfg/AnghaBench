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
struct wcove_typec {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
#define  TYPEC_CC_RP_1_5 129 
#define  TYPEC_CC_RP_3_0 128 
 int /*<<< orphan*/  USBC_CONTROL1 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_180 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_330 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_80 ; 
 unsigned int USBC_CONTROL1_DRPTOGGLE_RANDOM ; 
 unsigned int USBC_CONTROL1_MODE_DRP ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 

__attribute__((used)) static int wcove_start_drp_toggling(struct tcpc_dev *tcpc,
				    enum typec_cc_status cc)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);
	unsigned int usbc_ctrl;

	usbc_ctrl = USBC_CONTROL1_MODE_DRP | USBC_CONTROL1_DRPTOGGLE_RANDOM;

	switch (cc) {
	case TYPEC_CC_RP_1_5:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_180;
		break;
	case TYPEC_CC_RP_3_0:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_330;
		break;
	default:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_80;
		break;
	}

	return regmap_write(wcove->regmap, USBC_CONTROL1, usbc_ctrl);
}