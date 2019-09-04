#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int this04; } ;
struct TYPE_14__ {int this0a; int this0c; int this0e; int this10; int this28; int this54; int this58; int this5c; int /*<<< orphan*/  coefset; int /*<<< orphan*/  this14_array; TYPE_1__ this04; scalar_t__ this08; } ;
struct TYPE_13__ {TYPE_3__ eq; } ;
typedef  TYPE_2__ vortex_t ;
typedef  TYPE_3__ eqlzr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vortex_EqHw_Enable (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_EqHw_Program10Band (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_EqHw_SetSampleRate (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vortex_EqHw_ZeroState (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_Eqlzr_ReadAndSetActiveCoefSet (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_Eqlzr_SetA3dBypassGain (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_Eqlzr_SetBypass (TYPE_2__*,int) ; 

__attribute__((used)) static void vortex_Eqlzr_init(vortex_t * vortex)
{
	eqlzr_t *eq = &(vortex->eq);

	/* Object constructor */
	//eq->this04 = 0;
	eq->this08 = 0;		/* Bypass gain with EQ in use. */
	eq->this0a = 0x5999;
	eq->this0c = 0x5999;	/* Bypass gain with EQ disabled. */
	eq->this0e = 0x5999;

	eq->this10 = 0xa;	/* 10 eq frequency bands. */
	eq->this04.this04 = eq->this10;
	eq->this28 = 0x1;	/* if 1 => Allow read access to this130 (gains) */
	eq->this54 = 0x0;	/* if 1 => Dont Allow access to hardware (gains) */
	eq->this58 = 0xffff;
	eq->this5c = 0xffff;

	/* Set gains. */
	memset(eq->this14_array, 0, sizeof(eq->this14_array));

	/* Actual init. */
	vortex_EqHw_ZeroState(vortex);
	vortex_EqHw_SetSampleRate(vortex, 0x11);
	vortex_Eqlzr_ReadAndSetActiveCoefSet(vortex);

	vortex_EqHw_Program10Band(vortex, &(eq->coefset));
	vortex_Eqlzr_SetBypass(vortex, eq->this54);
	vortex_Eqlzr_SetA3dBypassGain(vortex, 0, 0);
	vortex_EqHw_Enable(vortex);
}