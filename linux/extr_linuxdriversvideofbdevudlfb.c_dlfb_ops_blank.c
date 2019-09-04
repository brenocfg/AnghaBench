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
struct urb {scalar_t__ transfer_buffer; } ;
struct fb_info {int /*<<< orphan*/  var; int /*<<< orphan*/  dev; struct dlfb_data* par; } ;
struct dlfb_data {int blank_mode; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 char* dlfb_blanking (char*,int) ; 
 char* dlfb_dummy_render (char*) ; 
 struct urb* dlfb_get_urb (struct dlfb_data*) ; 
 int /*<<< orphan*/  dlfb_set_video_mode (struct dlfb_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlfb_submit_urb (struct dlfb_data*,struct urb*,int) ; 
 char* dlfb_vidreg_lock (char*) ; 
 char* dlfb_vidreg_unlock (char*) ; 

__attribute__((used)) static int dlfb_ops_blank(int blank_mode, struct fb_info *info)
{
	struct dlfb_data *dlfb = info->par;
	char *bufptr;
	struct urb *urb;

	dev_dbg(info->dev, "blank, mode %d --> %d\n",
		dlfb->blank_mode, blank_mode);

	if ((dlfb->blank_mode == FB_BLANK_POWERDOWN) &&
	    (blank_mode != FB_BLANK_POWERDOWN)) {

		/* returning from powerdown requires a fresh modeset */
		dlfb_set_video_mode(dlfb, &info->var);
	}

	urb = dlfb_get_urb(dlfb);
	if (!urb)
		return 0;

	bufptr = (char *) urb->transfer_buffer;
	bufptr = dlfb_vidreg_lock(bufptr);
	bufptr = dlfb_blanking(bufptr, blank_mode);
	bufptr = dlfb_vidreg_unlock(bufptr);

	/* seems like a render op is needed to have blank change take effect */
	bufptr = dlfb_dummy_render(bufptr);

	dlfb_submit_urb(dlfb, urb, bufptr -
			(char *) urb->transfer_buffer);

	dlfb->blank_mode = blank_mode;

	return 0;
}