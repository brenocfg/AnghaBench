#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int this0e; int this0a; int this58; int this5c; scalar_t__ this54; } ;
struct TYPE_5__ {TYPE_2__ eq; } ;
typedef  TYPE_1__ vortex_t ;
typedef  int u32 ;
typedef  TYPE_2__ eqlzr_t ;

/* Variables and functions */
 int /*<<< orphan*/  vortex_EqHw_SetA3DBypassGain (TYPE_1__*,int,int) ; 

__attribute__((used)) static void vortex_Eqlzr_ProgramA3dBypassGain(vortex_t * vortex)
{
	eqlzr_t *eq = &(vortex->eq);
	u32 eax, ebx;

	if (eq->this54)
		eax = eq->this0e;
	else
		eax = eq->this0a;
	ebx = (eax * eq->this58) >> 0x10;
	eax = (eax * eq->this5c) >> 0x10;
	vortex_EqHw_SetA3DBypassGain(vortex, ebx, eax);
}