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
struct TYPE_2__ {size_t smem_len; scalar_t__ smem_start; } ;
struct fb_info {int /*<<< orphan*/  mm_lock; TYPE_1__ fix; int /*<<< orphan*/ * screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmap_video_memory(struct fb_info *info)
{
	void *p = info->screen_base;
	size_t l = info->fix.smem_len;

	mutex_lock(&info->mm_lock);
	info->screen_base = NULL;
	info->fix.smem_start = 0;
	info->fix.smem_len = 0;
	mutex_unlock(&info->mm_lock);

	if (p)
		free_pages_exact(p, l);
}