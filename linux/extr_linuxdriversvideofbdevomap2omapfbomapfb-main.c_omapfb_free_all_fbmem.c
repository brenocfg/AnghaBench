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
struct omapfb2_device {int num_fbs; struct fb_info** fbs; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  clear_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  omapfb_free_fbmem (struct fb_info*) ; 

__attribute__((used)) static int omapfb_free_all_fbmem(struct omapfb2_device *fbdev)
{
	int i;

	DBG("free all fbmem\n");

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct fb_info *fbi = fbdev->fbs[i];
		omapfb_free_fbmem(fbi);
		clear_fb_info(fbi);
	}

	return 0;
}