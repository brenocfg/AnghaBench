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
 scalar_t__ VORTEX_SRC_DRIFT0 ; 
 scalar_t__ VORTEX_SRC_DRIFT1 ; 
 scalar_t__ VORTEX_SRC_DRIFT2 ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void vortex_src_cleardrift(vortex_t * vortex, unsigned char src)
{
	hwwrite(vortex->mmio, VORTEX_SRC_DRIFT0 + (src << 2), 0);
	hwwrite(vortex->mmio, VORTEX_SRC_DRIFT1 + (src << 2), 0);
	hwwrite(vortex->mmio, VORTEX_SRC_DRIFT2 + (src << 2), 1);
}