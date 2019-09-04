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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ VORTEX_SRC_CHNBASE ; 
 scalar_t__ VORTEX_SRC_RTBASE ; 
 scalar_t__ VORTEX_SRC_SOURCESIZE ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void vortex_srcblock_init(vortex_t * vortex)
{
	u32 addr;
	int x;
	hwwrite(vortex->mmio, VORTEX_SRC_SOURCESIZE, 0x1ff);
	/*
	   for (x=0; x<0x10; x++) {
	   vortex_src_init(&vortex_src[x], x);
	   }
	 */
	//addr = 0xcc3c;
	//addr = 0x26c3c;
	addr = VORTEX_SRC_RTBASE + 0x3c;
	for (x = 0xf; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0);
		addr -= 4;
	}
	//addr = 0xcc94;
	//addr = 0x26c94;
	addr = VORTEX_SRC_CHNBASE + 0x54;
	for (x = 0x15; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0);
		addr -= 4;
	}
}