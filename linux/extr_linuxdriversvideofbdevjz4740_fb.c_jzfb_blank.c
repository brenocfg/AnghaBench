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
struct jzfb {int is_enabled; int /*<<< orphan*/  lock; } ;
struct fb_info {struct jzfb* par; } ;

/* Variables and functions */
#define  FB_BLANK_UNBLANK 128 
 int /*<<< orphan*/  jzfb_disable (struct jzfb*) ; 
 int /*<<< orphan*/  jzfb_enable (struct jzfb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jzfb_blank(int blank_mode, struct fb_info *info)
{
	struct jzfb *jzfb = info->par;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		mutex_lock(&jzfb->lock);
		if (jzfb->is_enabled) {
			mutex_unlock(&jzfb->lock);
			return 0;
		}

		jzfb_enable(jzfb);
		jzfb->is_enabled = 1;

		mutex_unlock(&jzfb->lock);
		break;
	default:
		mutex_lock(&jzfb->lock);
		if (!jzfb->is_enabled) {
			mutex_unlock(&jzfb->lock);
			return 0;
		}

		jzfb_disable(jzfb);
		jzfb->is_enabled = 0;

		mutex_unlock(&jzfb->lock);
		break;
	}

	return 0;
}