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
typedef  size_t uint16 ;

/* Variables and functions */
 size_t LOCKTAG_LAST_TYPE ; 
 char const** LockTagTypeNames ; 

const char *
GetLockNameFromTagType(uint16 locktag_type)
{
	if (locktag_type > LOCKTAG_LAST_TYPE)
		return "???";
	return LockTagTypeNames[locktag_type];
}