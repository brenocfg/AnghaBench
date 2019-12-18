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
#define  COMMIT_TS_SETTS 130 
#define  COMMIT_TS_TRUNCATE 129 
#define  COMMIT_TS_ZEROPAGE 128 

const char *
commit_ts_identify(uint8 info)
{
	switch (info)
	{
		case COMMIT_TS_ZEROPAGE:
			return "ZEROPAGE";
		case COMMIT_TS_TRUNCATE:
			return "TRUNCATE";
		case COMMIT_TS_SETTS:
			return "SETTS";
		default:
			return NULL;
	}
}