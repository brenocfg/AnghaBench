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
 int /*<<< orphan*/  A3dHrirImpulse ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosTarget (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetGainCurrent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  a3dsrc_SetGainTarget (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetHrtfTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetItdCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetItdTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetTimeConsts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a3dsrc_ProgramPipe(a3dsrc_t * a)
{
	a3dsrc_SetTimeConsts(a, 0, 0, 0, 0);
	a3dsrc_SetAtmosCurrent(a, 0, 0x4000, 0, 0, 0);
	a3dsrc_SetAtmosTarget(a, 0x4000, 0, 0, 0, 0);
	a3dsrc_SetItdCurrent(a, 0, 0);
	a3dsrc_SetItdTarget(a, 0, 0);
	a3dsrc_SetGainCurrent(a, 0x7fff, 0x7fff);
	a3dsrc_SetGainTarget(a, 0x7fff, 0x7fff);

	/* SET HRTF HERE */

	/* Single spike leads to identity transfer function. */
	a3dsrc_SetHrtfCurrent(a, A3dHrirImpulse, A3dHrirImpulse);
	a3dsrc_SetHrtfTarget(a, A3dHrirImpulse, A3dHrirImpulse);

	/* Test: Sounds saturated. */
	//a3dsrc_SetHrtfCurrent(a, A3dHrirSatTest, A3dHrirSatTest);
	//a3dsrc_SetHrtfTarget(a, A3dHrirSatTest, A3dHrirSatTest);      
}