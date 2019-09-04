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
 int hwread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vortex_XtalkHw_SetSampleRate(vortex_t * vortex, u32 sr)
{
	u32 temp;

	temp = (hwread(vortex->mmio, 0x24660) & 0x1FFFFFFF) | 0xC0000000;
	temp = (temp & 0xffffff07) | ((sr & 0x1f) << 3);
	hwwrite(vortex->mmio, 0x24660, temp);
}