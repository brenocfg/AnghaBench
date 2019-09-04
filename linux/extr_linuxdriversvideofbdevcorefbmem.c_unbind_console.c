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
struct fb_info {int node; } ;
struct fb_event {struct fb_info* info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FB_EVENT_FB_UNBIND ; 
 int FB_MAX ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int fb_notifier_call_chain (int /*<<< orphan*/ ,struct fb_event*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static int unbind_console(struct fb_info *fb_info)
{
	struct fb_event event;
	int ret;
	int i = fb_info->node;

	if (i < 0 || i >= FB_MAX || registered_fb[i] != fb_info)
		return -EINVAL;

	console_lock();
	if (!lock_fb_info(fb_info)) {
		console_unlock();
		return -ENODEV;
	}

	event.info = fb_info;
	ret = fb_notifier_call_chain(FB_EVENT_FB_UNBIND, &event);
	unlock_fb_info(fb_info);
	console_unlock();

	return ret;
}