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

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int function ; 
 int /*<<< orphan*/  isapnp_device_id ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char,char,int,int,int,int) ; 
 int vendor ; 

__attribute__((used)) static int do_isapnp_entry(const char *filename,
			   void *symval, char *alias)
{
	DEF_FIELD(symval, isapnp_device_id, vendor);
	DEF_FIELD(symval, isapnp_device_id, function);
	sprintf(alias, "pnp:d%c%c%c%x%x%x%x*",
		'A' + ((vendor >> 2) & 0x3f) - 1,
		'A' + (((vendor & 3) << 3) | ((vendor >> 13) & 7)) - 1,
		'A' + ((vendor >> 8) & 0x1f) - 1,
		(function >> 4) & 0x0f, function & 0x0f,
		(function >> 12) & 0x0f, (function >> 8) & 0x0f);
	return 1;
}