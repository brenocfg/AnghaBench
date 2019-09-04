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
struct TYPE_2__ {int pwr_op_mode; } ;
struct ucsi_connector {int /*<<< orphan*/  port; TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_PWR_MODE_1_5A ; 
 int /*<<< orphan*/  TYPEC_PWR_MODE_3_0A ; 
 int /*<<< orphan*/  TYPEC_PWR_MODE_PD ; 
 int /*<<< orphan*/  TYPEC_PWR_MODE_USB ; 
#define  UCSI_CONSTAT_PWR_OPMODE_PD 130 
#define  UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5 129 
#define  UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0 128 
 int /*<<< orphan*/  typec_set_pwr_opmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucsi_pwr_opmode_change(struct ucsi_connector *con)
{
	switch (con->status.pwr_op_mode) {
	case UCSI_CONSTAT_PWR_OPMODE_PD:
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_PD);
		break;
	case UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_1_5A);
		break;
	case UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_3_0A);
		break;
	default:
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_USB);
		break;
	}
}