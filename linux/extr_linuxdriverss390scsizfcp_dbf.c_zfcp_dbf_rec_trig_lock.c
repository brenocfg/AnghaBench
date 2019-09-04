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
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_port {int dummy; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_trig (char*,struct zfcp_adapter*,struct zfcp_port*,struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_dbf_rec_trig_lock(char *tag, struct zfcp_adapter *adapter,
			    struct zfcp_port *port, struct scsi_device *sdev,
			    u8 want, u8 need)
{
	unsigned long flags;

	read_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_dbf_rec_trig(tag, adapter, port, sdev, want, need);
	read_unlock_irqrestore(&adapter->erp_lock, flags);
}