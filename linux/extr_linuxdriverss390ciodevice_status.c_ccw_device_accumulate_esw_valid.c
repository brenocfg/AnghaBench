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
struct TYPE_3__ {int stctl; int actl; int /*<<< orphan*/  eswf; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;

/* Variables and functions */
 int SCSW_ACTL_SUSPENDED ; 
 int SCSW_STCTL_INTER_STATUS ; 
 int SCSW_STCTL_STATUS_PEND ; 

__attribute__((used)) static int
ccw_device_accumulate_esw_valid(struct irb *irb)
{
	if (!irb->scsw.cmd.eswf &&
	    (irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND))
		return 0;
	if (irb->scsw.cmd.stctl ==
			(SCSW_STCTL_INTER_STATUS|SCSW_STCTL_STATUS_PEND) &&
	    !(irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		return 0;
	return 1;
}