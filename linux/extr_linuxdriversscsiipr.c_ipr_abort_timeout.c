#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct ipr_ioa_cfg {TYPE_4__* host; scalar_t__ in_reset_reload; } ;
struct ipr_cmd_pkt {int* cdb; int /*<<< orphan*/  request_type; } ;
struct TYPE_7__ {struct ipr_cmd_pkt cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  sdev; } ;
struct TYPE_5__ {scalar_t__ done; } ;
struct ipr_cmnd {TYPE_3__ ioarcb; struct ipr_cmnd* sibling; TYPE_2__ u; TYPE_1__ completion; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_BUS_RESET ; 
 int /*<<< orphan*/  IPR_DEVICE_RESET_TIMEOUT ; 
 int IPR_RESET_DEVICE ; 
 int IPR_RESET_TYPE_SELECT ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LEAVE ; 
 struct ipr_cmnd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_bus_reset_done ; 
 struct ipr_cmnd* ipr_cmd ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipr_cmnd* ipr_get_free_ipr_cmnd (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_timeout ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ipr_abort_timeout(struct timer_list *t)
{
	struct ipr_cmnd *ipr_cmd = from_timer(ipr_cmd, t, timer);
	struct ipr_cmnd *reset_cmd;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_cmd_pkt *cmd_pkt;
	unsigned long lock_flags = 0;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	if (ipr_cmd->completion.done || ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		return;
	}

	sdev_printk(KERN_ERR, ipr_cmd->u.sdev, "Abort timed out. Resetting bus.\n");
	reset_cmd = ipr_get_free_ipr_cmnd(ioa_cfg);
	ipr_cmd->sibling = reset_cmd;
	reset_cmd->sibling = ipr_cmd;
	reset_cmd->ioarcb.res_handle = ipr_cmd->ioarcb.res_handle;
	cmd_pkt = &reset_cmd->ioarcb.cmd_pkt;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_RESET_DEVICE;
	cmd_pkt->cdb[2] = IPR_RESET_TYPE_SELECT | IPR_BUS_RESET;

	ipr_do_req(reset_cmd, ipr_bus_reset_done, ipr_timeout, IPR_DEVICE_RESET_TIMEOUT);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
}