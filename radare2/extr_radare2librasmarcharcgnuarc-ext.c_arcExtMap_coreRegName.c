#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* coreRegisters; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 int FIRST_EXTENSION_CORE_REGISTER ; 
 int LAST_EXTENSION_CORE_REGISTER ; 
 TYPE_2__ arc_extension_map ; 

const char *
arcExtMap_coreRegName (int regnum)
{
	if (regnum < FIRST_EXTENSION_CORE_REGISTER || regnum > LAST_EXTENSION_CORE_REGISTER) {
		return NULL;
	}
	return arc_extension_map.coreRegisters[regnum - FIRST_EXTENSION_CORE_REGISTER].name;
}