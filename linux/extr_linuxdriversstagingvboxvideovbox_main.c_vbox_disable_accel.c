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
struct vbox_private {unsigned int num_crtcs; int /*<<< orphan*/  guest_pool; int /*<<< orphan*/ * vbva_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  vbva_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

void vbox_disable_accel(struct vbox_private *vbox)
{
	unsigned int i;

	for (i = 0; i < vbox->num_crtcs; ++i)
		vbva_disable(&vbox->vbva_info[i], vbox->guest_pool, i);
}