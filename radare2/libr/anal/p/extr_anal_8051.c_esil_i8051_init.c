#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ user; } ;
struct TYPE_4__ {TYPE_2__ cb; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int i8051_is_init ; 
 TYPE_2__ ocbs ; 

__attribute__((used)) static int esil_i8051_init (RAnalEsil *esil) {
	if (esil->cb.user) {
		return true;
	}
	ocbs = esil->cb;
	/* these hooks break esil emulation */
	/* pc is not read properly, mem mapped registers are not shown in ar, ... */
	/* all 8051 regs are mem mapped, and reg access via mem is very common */
//  disabled to make esil work, before digging deeper
//	esil->cb.hook_reg_read = i8051_hook_reg_read;
//	esil->cb.hook_reg_write = i8051_hook_reg_write;
	i8051_is_init = true;
	return true;
}