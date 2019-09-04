#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * a3d; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int NR_A3D ; 
 int /*<<< orphan*/  Vort3DRend_Initialize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_HEADPHONE ; 
 int /*<<< orphan*/  a3dsrc_ZeroStateA3D (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_A3dSourceHw_Initialize (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vortex_a3d_register_controls (TYPE_1__*) ; 

__attribute__((used)) static void vortex_Vort3D_enable(vortex_t *v)
{
	int i;

	Vort3DRend_Initialize(v, XT_HEADPHONE);
	for (i = 0; i < NR_A3D; i++) {
		vortex_A3dSourceHw_Initialize(v, i % 4, i >> 2);
		a3dsrc_ZeroStateA3D(&v->a3d[0], v);
	}
	/* Register ALSA controls */
	vortex_a3d_register_controls(v);
}