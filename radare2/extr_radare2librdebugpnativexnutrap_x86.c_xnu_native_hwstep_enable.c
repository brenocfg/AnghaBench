#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bits; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 scalar_t__ R_SYS_BITS_64 ; 
 int xnu_x86_hwstep_enable32 (TYPE_1__*,int) ; 
 int xnu_x86_hwstep_enable64 (TYPE_1__*,int) ; 

bool xnu_native_hwstep_enable(RDebug *dbg, bool enable) {
	if (dbg->bits == R_SYS_BITS_64)
		return xnu_x86_hwstep_enable64 (dbg, enable);
	return xnu_x86_hwstep_enable32 (dbg, enable);
}