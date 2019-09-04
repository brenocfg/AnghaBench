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
struct fb_info {struct arcfb_par* par; } ;
struct arcfb_par {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arcfb_release(struct fb_info *info, int user)
{
	struct arcfb_par *par = info->par;
	int count = atomic_read(&par->ref_count);

	if (!count)
		return -EINVAL;
	atomic_dec(&par->ref_count);
	return 0;
}