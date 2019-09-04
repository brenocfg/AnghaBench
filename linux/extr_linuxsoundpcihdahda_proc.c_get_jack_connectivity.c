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
typedef  int u32 ;

/* Variables and functions */
 int AC_DEFCFG_LOCATION_SHIFT ; 

__attribute__((used)) static const char *get_jack_connectivity(u32 cfg)
{
	static const char * const jack_locations[4] = {
		"Ext", "Int", "Sep", "Oth"
	};

	return jack_locations[(cfg >> (AC_DEFCFG_LOCATION_SHIFT + 4)) & 3];
}