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
 scalar_t__ VORTEX_SRC_DATA ; 
 scalar_t__ VORTEX_SRC_DATA0 ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_src_flushbuffers(vortex_t * vortex, unsigned char src)
{
	int i;

	for (i = 0x1f; i >= 0; i--)
		hwwrite(vortex->mmio,
			VORTEX_SRC_DATA0 + (src << 7) + (i << 2), 0);
	hwwrite(vortex->mmio, VORTEX_SRC_DATA + (src << 3), 0);
	hwwrite(vortex->mmio, VORTEX_SRC_DATA + (src << 3) + 4, 0);
}