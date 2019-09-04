#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  callback; int /*<<< orphan*/ * cdb; } ;
typedef  TYPE_1__ ips_scb_t ;
struct TYPE_9__ {int /*<<< orphan*/  cmd_in_progress; int /*<<< orphan*/  waitflag; } ;
typedef  TYPE_2__ ips_ha_t ;

/* Variables and functions */
 int IPS_FAILURE ; 
 int IPS_FFDC ; 
 int IPS_SUCCESS_IMM ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int ips_send_cmd (TYPE_2__*,TYPE_1__*) ; 
 int ips_wait (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ipsintr_blocking ; 

__attribute__((used)) static int
ips_send_wait(ips_ha_t * ha, ips_scb_t * scb, int timeout, int intr)
{
	int ret;

	METHOD_TRACE("ips_send_wait", 1);

	if (intr != IPS_FFDC) {	/* Won't be Waiting if this is a Time Stamp */
		ha->waitflag = TRUE;
		ha->cmd_in_progress = scb->cdb[0];
	}
	scb->callback = ipsintr_blocking;
	ret = ips_send_cmd(ha, scb);

	if ((ret == IPS_FAILURE) || (ret == IPS_SUCCESS_IMM))
		return (ret);

	if (intr != IPS_FFDC)	/* Don't Wait around if this is a Time Stamp */
		ret = ips_wait(ha, timeout, intr);

	return (ret);
}