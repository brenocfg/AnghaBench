#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fc_port {scalar_t__ chip_reset; scalar_t__ scan_state; int /*<<< orphan*/  fw_login_state; scalar_t__ logo_ack_needed; scalar_t__ logout_on_delete; TYPE_3__* vha; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_5__ {TYPE_1__* base_qpair; } ;
struct TYPE_4__ {scalar_t__ chip_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_LS_PORT_UNAVAIL ; 

__attribute__((used)) static void qla24xx_chk_fcp_state(struct fc_port *sess)
{
	if (sess->chip_reset != sess->vha->hw->base_qpair->chip_reset) {
		sess->logout_on_delete = 0;
		sess->logo_ack_needed = 0;
		sess->fw_login_state = DSC_LS_PORT_UNAVAIL;
		sess->scan_state = 0;
	}
}