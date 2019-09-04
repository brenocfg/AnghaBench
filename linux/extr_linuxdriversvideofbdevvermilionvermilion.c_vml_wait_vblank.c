#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vml_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void vml_wait_vblank(struct vml_info *vinfo)
{
	/* Wait for vblank. For now, just wait for a 50Hz cycle (20ms)) */
	mdelay(20);
}