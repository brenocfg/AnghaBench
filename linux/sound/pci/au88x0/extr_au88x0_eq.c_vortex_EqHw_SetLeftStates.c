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
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_EqHw_SetLeftStates(vortex_t * vortex, u16 a[], u16 b[])
{
	eqhw_t *eqhw = &(vortex->eq.this04);
	int i = 0, ebx;

	hwwrite(vortex->mmio, 0x2b3fc, a[0]);
	hwwrite(vortex->mmio, 0x2b400, a[1]);

	for (ebx = 0; ebx < eqhw->this04; ebx++) {
		hwwrite(vortex->mmio, 0x2b014 + (i * 0xc), b[i]);
		hwwrite(vortex->mmio, 0x2b018 + (i * 0xc), b[1 + i]);
		hwwrite(vortex->mmio, 0x2b01c + (i * 0xc), b[2 + i]);
		hwwrite(vortex->mmio, 0x2b020 + (i * 0xc), b[3 + i]);
		i += 4;
	}
}