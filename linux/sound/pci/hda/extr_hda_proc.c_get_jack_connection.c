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
typedef  size_t u32 ;

/* Variables and functions */
 size_t AC_DEFCFG_CONN_TYPE ; 
 size_t AC_DEFCFG_CONN_TYPE_SHIFT ; 

__attribute__((used)) static const char *get_jack_connection(u32 cfg)
{
	static const char * const names[16] = {
		"Unknown", "1/8", "1/4", "ATAPI",
		"RCA", "Optical","Digital", "Analog",
		"DIN", "XLR", "RJ11", "Comb",
		NULL, NULL, NULL, "Other"
	};
	cfg = (cfg & AC_DEFCFG_CONN_TYPE) >> AC_DEFCFG_CONN_TYPE_SHIFT;
	if (names[cfg])
		return names[cfg];
	else
		return "UNKNOWN";
}