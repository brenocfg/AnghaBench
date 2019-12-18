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
struct TYPE_4__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_5__ {int slice; scalar_t__ vortex; } ;
typedef  TYPE_2__ a3dsrc_t ;

/* Variables and functions */
 scalar_t__ A3D_SLICE_Control ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 

__attribute__((used)) static void a3dsrc_SetA3DControlReg(a3dsrc_t * a, unsigned long ctrl)
{
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwwrite(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd), ctrl);
}