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
struct i740fb_par {scalar_t__ ref_count; int /*<<< orphan*/  open_lock; } ;
struct fb_info {struct i740fb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i740fb_release(struct fb_info *info, int user)
{
	struct i740fb_par *par = info->par;

	mutex_lock(&(par->open_lock));
	if (par->ref_count == 0) {
		fb_err(info, "release called with zero refcount\n");
		mutex_unlock(&(par->open_lock));
		return -EINVAL;
	}

	par->ref_count--;
	mutex_unlock(&(par->open_lock));

	return 0;
}