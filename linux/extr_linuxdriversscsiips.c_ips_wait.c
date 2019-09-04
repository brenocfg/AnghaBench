#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* intr ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int waitflag; TYPE_1__ func; } ;
typedef  TYPE_2__ ips_ha_t ;

/* Variables and functions */
 int FALSE ; 
 int IPS_FAILURE ; 
 int IPS_INTR_IORL ; 
 int IPS_INTR_ON ; 
 int IPS_ONE_SEC ; 
 int IPS_SUCCESS ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
ips_wait(ips_ha_t * ha, int time, int intr)
{
	int ret;
	int done;

	METHOD_TRACE("ips_wait", 1);

	ret = IPS_FAILURE;
	done = FALSE;

	time *= IPS_ONE_SEC;	/* convert seconds */

	while ((time > 0) && (!done)) {
		if (intr == IPS_INTR_ON) {
			if (ha->waitflag == FALSE) {
				ret = IPS_SUCCESS;
				done = TRUE;
				break;
			}
		} else if (intr == IPS_INTR_IORL) {
			if (ha->waitflag == FALSE) {
				/*
				 * controller generated an interrupt to
				 * acknowledge completion of the command
				 * and ips_intr() has serviced the interrupt.
				 */
				ret = IPS_SUCCESS;
				done = TRUE;
				break;
			}

			/*
			 * NOTE: we already have the io_request_lock so
			 * even if we get an interrupt it won't get serviced
			 * until after we finish.
			 */

			(*ha->func.intr) (ha);
		}

		/* This looks like a very evil loop, but it only does this during start-up */
		udelay(1000);
		time--;
	}

	return (ret);
}