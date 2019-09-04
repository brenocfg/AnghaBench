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
struct fb_info {int /*<<< orphan*/  dev; struct fb_deferred_io* fbdefio; struct dlfb_data* par; } ;
struct fb_deferred_io {int /*<<< orphan*/  deferred_io; int /*<<< orphan*/  delay; } ;
struct dlfb_data {int /*<<< orphan*/  fb_count; scalar_t__ virtualized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFIO_WRITE_DELAY ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  console ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlfb_dpy_deferred_io ; 
 int /*<<< orphan*/  fb_deferred_io_init (struct fb_info*) ; 
 scalar_t__ fb_defio ; 
 struct fb_deferred_io* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlfb_ops_open(struct fb_info *info, int user)
{
	struct dlfb_data *dlfb = info->par;

	/*
	 * fbcon aggressively connects to first framebuffer it finds,
	 * preventing other clients (X) from working properly. Usually
	 * not what the user wants. Fail by default with option to enable.
	 */
	if ((user == 0) && (!console))
		return -EBUSY;

	/* If the USB device is gone, we don't accept new opens */
	if (dlfb->virtualized)
		return -ENODEV;

	dlfb->fb_count++;

	if (fb_defio && (info->fbdefio == NULL)) {
		/* enable defio at last moment if not disabled by client */

		struct fb_deferred_io *fbdefio;

		fbdefio = kzalloc(sizeof(struct fb_deferred_io), GFP_KERNEL);

		if (fbdefio) {
			fbdefio->delay = DL_DEFIO_WRITE_DELAY;
			fbdefio->deferred_io = dlfb_dpy_deferred_io;
		}

		info->fbdefio = fbdefio;
		fb_deferred_io_init(info);
	}

	dev_dbg(info->dev, "open, user=%d fb_info=%p count=%d\n",
		user, info, dlfb->fb_count);

	return 0;
}