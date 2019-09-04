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
struct neofb_par {TYPE_1__* neo2200; } ;
struct fb_info {struct neofb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  bltStat; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int neo2200_sync(struct fb_info *info)
{
	struct neofb_par *par = info->par;

	while (readl(&par->neo2200->bltStat) & 1)
		cpu_relax();
	return 0;
}