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
struct pm2fb_par {int dummy; } ;
struct fb_info {struct pm2fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_OUT_FIFO ; 
 int /*<<< orphan*/  PM2R_OUT_FIFO_WORDS ; 
 int /*<<< orphan*/  PM2R_SYNC ; 
 scalar_t__ PM2TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ pm2_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2fb_sync(struct fb_info *info)
{
	struct pm2fb_par *par = info->par;

	WAIT_FIFO(par, 1);
	pm2_WR(par, PM2R_SYNC, 0);
	mb();
	do {
		while (pm2_RD(par, PM2R_OUT_FIFO_WORDS) == 0)
			cpu_relax();
	} while (pm2_RD(par, PM2R_OUT_FIFO) != PM2TAG(PM2R_SYNC));

	return 0;
}