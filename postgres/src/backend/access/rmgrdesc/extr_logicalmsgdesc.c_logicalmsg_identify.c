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
 int XLOG_LOGICAL_MESSAGE ; 
 int XLR_INFO_MASK ; 

const char *
logicalmsg_identify(uint8 info)
{
	if ((info & ~XLR_INFO_MASK) == XLOG_LOGICAL_MESSAGE)
		return "MESSAGE";

	return NULL;
}