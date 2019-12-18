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
struct TYPE_2__ {int r; } ;

/* Variables and functions */
 int VT_LLOCAL ; 
 int VT_LOCAL ; 
 int VT_LVAL ; 
 int VT_LVAL_TYPE ; 
 int VT_VALMASK ; 
 TYPE_1__* vtop ; 

__attribute__((used)) static void gaddrof(void) {
	vtop->r &= ~VT_LVAL;
	/* tricky: if saved lvalue, then we can go back to lvalue */
	if ((vtop->r & VT_VALMASK) == VT_LLOCAL) {
		vtop->r = (vtop->r & ~(VT_VALMASK | VT_LVAL_TYPE)) | VT_LOCAL | VT_LVAL;
	}
}