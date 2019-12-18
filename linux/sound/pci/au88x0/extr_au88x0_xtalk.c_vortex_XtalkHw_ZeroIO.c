#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_XtalkHw_ZeroIO(vortex_t * vortex)
{
	int i;

	for (i = 0; i < 20; i++)
		hwwrite(vortex->mmio, 0x24600 + (i << 2), 0);
	for (i = 0; i < 4; i++)
		hwwrite(vortex->mmio, 0x24650 + (i << 2), 0);
}