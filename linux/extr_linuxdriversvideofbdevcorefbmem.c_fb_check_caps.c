#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {TYPE_1__* fbops; } ;
struct fb_event {struct fb_blit_caps* data; struct fb_info* info; } ;
struct fb_blit_caps {int flags; int x; int y; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  fbcaps ;
typedef  int /*<<< orphan*/  caps ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_get_caps ) (struct fb_info*,struct fb_blit_caps*,struct fb_var_screeninfo*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int FB_ACTIVATE_ALL ; 
 int /*<<< orphan*/  FB_EVENT_GET_REQ ; 
 int /*<<< orphan*/  fb_notifier_call_chain (int /*<<< orphan*/ ,struct fb_event*) ; 
 int /*<<< orphan*/  memset (struct fb_blit_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_blit_caps*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int fb_check_caps(struct fb_info *info, struct fb_var_screeninfo *var,
			 u32 activate)
{
	struct fb_event event;
	struct fb_blit_caps caps, fbcaps;
	int err = 0;

	memset(&caps, 0, sizeof(caps));
	memset(&fbcaps, 0, sizeof(fbcaps));
	caps.flags = (activate & FB_ACTIVATE_ALL) ? 1 : 0;
	event.info = info;
	event.data = &caps;
	fb_notifier_call_chain(FB_EVENT_GET_REQ, &event);
	info->fbops->fb_get_caps(info, &fbcaps, var);

	if (((fbcaps.x ^ caps.x) & caps.x) ||
	    ((fbcaps.y ^ caps.y) & caps.y) ||
	    (fbcaps.len < caps.len))
		err = -EINVAL;

	return err;
}