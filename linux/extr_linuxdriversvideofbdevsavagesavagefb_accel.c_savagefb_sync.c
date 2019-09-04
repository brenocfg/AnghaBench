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
struct savagefb_par {int /*<<< orphan*/  (* SavageWaitIdle ) (struct savagefb_par*) ;} ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct savagefb_par*) ; 

int savagefb_sync(struct fb_info *info)
{
	struct savagefb_par *par = info->par;

	par->SavageWaitIdle(par);
	return 0;
}