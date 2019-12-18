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
#define  XLOG_MULTIXACT_CREATE_ID 131 
#define  XLOG_MULTIXACT_TRUNCATE_ID 130 
#define  XLOG_MULTIXACT_ZERO_MEM_PAGE 129 
#define  XLOG_MULTIXACT_ZERO_OFF_PAGE 128 
 int XLR_INFO_MASK ; 

const char *
multixact_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_MULTIXACT_ZERO_OFF_PAGE:
			id = "ZERO_OFF_PAGE";
			break;
		case XLOG_MULTIXACT_ZERO_MEM_PAGE:
			id = "ZERO_MEM_PAGE";
			break;
		case XLOG_MULTIXACT_CREATE_ID:
			id = "CREATE_ID";
			break;
		case XLOG_MULTIXACT_TRUNCATE_ID:
			id = "TRUNCATE_ID";
			break;
	}

	return id;
}