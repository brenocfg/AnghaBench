#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int this04; } ;
struct TYPE_5__ {TYPE_3__ this04; } ;
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_1__ eq; } ;
typedef  TYPE_2__ vortex_t ;
typedef  int /*<<< orphan*/  u16 ;
typedef  TYPE_3__ eqhw_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwread (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vortex_EqHw_GetTenBandLevels(vortex_t * vortex, u16 peaks[])
{
	eqhw_t *eqhw = &(vortex->eq.this04);
	int i;

	if (eqhw->this04 <= 0)
		return;

	for (i = 0; i < eqhw->this04; i++)
		peaks[i] = hwread(vortex->mmio, 0x2B024 + i * 0x30);
	for (i = 0; i < eqhw->this04; i++)
		peaks[i + eqhw->this04] =
		    hwread(vortex->mmio, 0x2B204 + i * 0x30);
}