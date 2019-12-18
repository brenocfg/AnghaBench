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
typedef  int uint8 ;

/* Variables and functions */
#define  XLOG_INVALIDATIONS 130 
#define  XLOG_RUNNING_XACTS 129 
#define  XLOG_STANDBY_LOCK 128 
 int XLR_INFO_MASK ; 

const char *
standby_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_STANDBY_LOCK:
			id = "LOCK";
			break;
		case XLOG_RUNNING_XACTS:
			id = "RUNNING_XACTS";
			break;
		case XLOG_INVALIDATIONS:
			id = "INVALIDATIONS";
			break;
	}

	return id;
}