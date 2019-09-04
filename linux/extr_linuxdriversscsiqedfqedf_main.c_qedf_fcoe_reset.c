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
struct fc_lport {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qedf_ctx_soft_reset (struct fc_lport*) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int qedf_fcoe_reset(struct Scsi_Host *shost)
{
	struct fc_lport *lport = shost_priv(shost);

	qedf_ctx_soft_reset(lport);
	return 0;
}