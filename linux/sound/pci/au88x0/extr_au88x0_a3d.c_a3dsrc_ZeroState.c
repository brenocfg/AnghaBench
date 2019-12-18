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
typedef  int /*<<< orphan*/  a3dsrc_t ;

/* Variables and functions */
 int /*<<< orphan*/  A3dHrirZeros ; 
 int /*<<< orphan*/  A3dItdDlineZeros ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetGainCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetGainTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfOutput (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetItdCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetItdDline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetItdTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetTimeConsts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a3dsrc_ZeroState(a3dsrc_t * a)
{
	/*
	pr_debug( "vortex: ZeroState slice: %d, source %d\n",
	       a->slice, a->source);
	*/
	a3dsrc_SetAtmosState(a, 0, 0, 0, 0);
	a3dsrc_SetHrtfState(a, A3dHrirZeros, A3dHrirZeros);
	a3dsrc_SetItdDline(a, A3dItdDlineZeros);
	a3dsrc_SetHrtfOutput(a, 0, 0);
	a3dsrc_SetTimeConsts(a, 0, 0, 0, 0);

	a3dsrc_SetAtmosCurrent(a, 0, 0, 0, 0, 0);
	a3dsrc_SetAtmosTarget(a, 0, 0, 0, 0, 0);
	a3dsrc_SetItdCurrent(a, 0, 0);
	a3dsrc_SetItdTarget(a, 0, 0);
	a3dsrc_SetGainCurrent(a, 0, 0);
	a3dsrc_SetGainTarget(a, 0, 0);

	a3dsrc_SetHrtfCurrent(a, A3dHrirZeros, A3dHrirZeros);
	a3dsrc_SetHrtfTarget(a, A3dHrirZeros, A3dHrirZeros);
}