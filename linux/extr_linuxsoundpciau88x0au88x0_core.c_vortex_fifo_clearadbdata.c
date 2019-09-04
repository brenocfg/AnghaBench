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
 int FIFO_SIZE_BITS ; 
 scalar_t__ VORTEX_FIFO_ADBDATA ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_fifo_clearadbdata(vortex_t * vortex, int fifo, int x)
{
	for (x--; x >= 0; x--)
		hwwrite(vortex->mmio,
			VORTEX_FIFO_ADBDATA +
			(((fifo << FIFO_SIZE_BITS) + x) << 2), 0);
}