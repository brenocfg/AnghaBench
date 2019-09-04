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
struct TYPE_13__ {TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_14__ {int /*<<< orphan*/ * vortex; } ;
typedef  TYPE_3__ a3dsrc_t ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CoefTCDefault ; 
 int /*<<< orphan*/  GainTCDefault ; 
 int /*<<< orphan*/  HrtfTCDefault ; 
 int /*<<< orphan*/  ItdTCDefault ; 
 int /*<<< orphan*/  a3dsrc_DisableA3D (TYPE_3__*) ; 
 int /*<<< orphan*/  a3dsrc_EnableA3D (TYPE_3__*) ; 
 int /*<<< orphan*/  a3dsrc_ProgramPipe (TYPE_3__*) ; 
 int /*<<< orphan*/  a3dsrc_SetA3DSampleRate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  a3dsrc_SetTimeConsts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_ZeroState (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vortex_Vort3D_InitializeSource(a3dsrc_t *a, int en, vortex_t *v)
{
	if (a->vortex == NULL) {
		dev_warn(v->card->dev,
			 "Vort3D_InitializeSource: A3D source not initialized\n");
		return;
	}
	if (en) {
		a3dsrc_ProgramPipe(a);
		a3dsrc_SetA3DSampleRate(a, 0x11);
		a3dsrc_SetTimeConsts(a, HrtfTCDefault,
				     ItdTCDefault, GainTCDefault,
				     CoefTCDefault);
		/* Remark: zero gain is muted. */
		//a3dsrc_SetGainTarget(a,0,0);
		//a3dsrc_SetGainCurrent(a,0,0);
		a3dsrc_EnableA3D(a);
	} else {
		a3dsrc_DisableA3D(a);
		a3dsrc_ZeroState(a);
	}
}