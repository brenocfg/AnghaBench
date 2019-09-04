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
typedef  int /*<<< orphan*/  u32 ;
struct fc_rport {int /*<<< orphan*/  dev_loss_tmo; } ;

/* Variables and functions */

__attribute__((used)) static void zfcp_scsi_set_rport_dev_loss_tmo(struct fc_rport *rport,
					     u32 timeout)
{
	rport->dev_loss_tmo = timeout;
}