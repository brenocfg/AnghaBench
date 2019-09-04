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
struct via_aux_drv {struct fb_monspecs* data; } ;
struct fb_monspecs {int /*<<< orphan*/  modedb; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_destroy_modedb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup(struct via_aux_drv *drv)
{
	struct fb_monspecs *spec = drv->data;

	if (spec)
		fb_destroy_modedb(spec->modedb);
}