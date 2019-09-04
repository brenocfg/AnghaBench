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
struct scsi_cmnd {TYPE_2__* device; } ;
struct qlogicfas408_priv {int qabort; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int SUCCESS ; 
 struct qlogicfas408_priv* get_priv_by_cmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ql_zap (struct qlogicfas408_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int qlogicfas408_host_reset(struct scsi_cmnd *cmd)
{
	struct qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	unsigned long flags;

	priv->qabort = 2;

	spin_lock_irqsave(cmd->device->host->host_lock, flags);
	ql_zap(priv);
	spin_unlock_irqrestore(cmd->device->host->host_lock, flags);

	return SUCCESS;
}