#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xenfb_info {int /*<<< orphan*/  fb; int /*<<< orphan*/  gfns; scalar_t__ page; TYPE_1__* fb_info; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 struct xenfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  framebuffer_release (TYPE_1__*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct xenfb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenfb_disconnect_backend (struct xenfb_info*) ; 

__attribute__((used)) static int xenfb_remove(struct xenbus_device *dev)
{
	struct xenfb_info *info = dev_get_drvdata(&dev->dev);

	xenfb_disconnect_backend(info);
	if (info->fb_info) {
		fb_deferred_io_cleanup(info->fb_info);
		unregister_framebuffer(info->fb_info);
		fb_dealloc_cmap(&info->fb_info->cmap);
		framebuffer_release(info->fb_info);
	}
	free_page((unsigned long)info->page);
	vfree(info->gfns);
	vfree(info->fb);
	kfree(info);

	return 0;
}