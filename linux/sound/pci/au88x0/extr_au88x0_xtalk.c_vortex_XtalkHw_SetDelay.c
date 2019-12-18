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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
vortex_XtalkHw_SetDelay(vortex_t * vortex, unsigned short right,
			unsigned short left)
{
	u32 esp0 = 0;

	esp0 &= 0x1FFFFFFF;
	esp0 |= 0xA0000000;
	esp0 = (esp0 & 0xffffE0ff) | ((right & 0x1F) << 8);
	esp0 = (esp0 & 0xfffc1fff) | ((left & 0x1F) << 0xd);

	hwwrite(vortex->mmio, 0x24660, esp0);
}