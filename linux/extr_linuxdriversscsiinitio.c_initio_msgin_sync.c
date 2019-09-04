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
struct initio_host {char* msg; TYPE_1__* active_tc; } ;
struct TYPE_2__ {size_t flags; } ;

/* Variables and functions */
 char MAX_OFFSET ; 
 size_t TCF_SCSI_RATE ; 
 char* initio_rate_tbl ; 

__attribute__((used)) static int initio_msgin_sync(struct initio_host * host)
{
	char default_period;

	default_period = initio_rate_tbl[host->active_tc->flags & TCF_SCSI_RATE];
	if (host->msg[3] > MAX_OFFSET) {
		host->msg[3] = MAX_OFFSET;
		if (host->msg[2] < default_period) {
			host->msg[2] = default_period;
			return 1;
		}
		if (host->msg[2] >= 59)	/* Change to async              */
			host->msg[3] = 0;
		return 1;
	}
	/* offset requests asynchronous transfers ? */
	if (host->msg[3] == 0) {
		return 0;
	}
	if (host->msg[2] < default_period) {
		host->msg[2] = default_period;
		return 1;
	}
	if (host->msg[2] >= 59) {
		host->msg[3] = 0;
		return 1;
	}
	return 0;
}