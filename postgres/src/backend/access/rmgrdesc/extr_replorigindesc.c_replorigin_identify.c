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
#define  XLOG_REPLORIGIN_DROP 129 
#define  XLOG_REPLORIGIN_SET 128 

const char *
replorigin_identify(uint8 info)
{
	switch (info)
	{
		case XLOG_REPLORIGIN_SET:
			return "SET";
		case XLOG_REPLORIGIN_DROP:
			return "DROP";
		default:
			return NULL;
	}
}