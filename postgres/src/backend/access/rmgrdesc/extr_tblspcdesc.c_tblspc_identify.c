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
#define  XLOG_TBLSPC_CREATE 129 
#define  XLOG_TBLSPC_DROP 128 
 int XLR_INFO_MASK ; 

const char *
tblspc_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_TBLSPC_CREATE:
			id = "CREATE";
			break;
		case XLOG_TBLSPC_DROP:
			id = "DROP";
			break;
	}

	return id;
}