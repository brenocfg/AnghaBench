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
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int /*<<< orphan*/  open; } ;

/* Variables and functions */

__attribute__((used)) static int atyfb_open(struct fb_info *info, int user)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;

	if (user) {
		par->open++;
#ifdef __sparc__
		par->mmaped = 0;
#endif
	}
	return 0;
}