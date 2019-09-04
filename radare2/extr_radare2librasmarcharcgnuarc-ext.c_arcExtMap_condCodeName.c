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
struct TYPE_2__ {char const** condCodes; } ;

/* Variables and functions */
 int FIRST_EXTENSION_CONDITION_CODE ; 
 int LAST_EXTENSION_CONDITION_CODE ; 
 TYPE_1__ arc_extension_map ; 

const char *
arcExtMap_condCodeName (int code)
{
	if (code < FIRST_EXTENSION_CONDITION_CODE || code > LAST_EXTENSION_CONDITION_CODE) {
		return NULL;
	}
	return arc_extension_map.condCodes[code - FIRST_EXTENSION_CONDITION_CODE];
}