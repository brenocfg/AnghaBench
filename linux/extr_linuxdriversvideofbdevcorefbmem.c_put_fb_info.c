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
struct fb_info {TYPE_1__* fbops; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_destroy ) (struct fb_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 

__attribute__((used)) static void put_fb_info(struct fb_info *fb_info)
{
	if (!atomic_dec_and_test(&fb_info->count))
		return;
	if (fb_info->fbops->fb_destroy)
		fb_info->fbops->fb_destroy(fb_info);
}