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
struct riva_par {int dummy; } ;
struct fb_info {struct riva_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_for_idle (struct riva_par*) ; 

__attribute__((used)) static int rivafb_sync(struct fb_info *info)
{
	struct riva_par *par = info->par;

	wait_for_idle(par);
	return 0;
}