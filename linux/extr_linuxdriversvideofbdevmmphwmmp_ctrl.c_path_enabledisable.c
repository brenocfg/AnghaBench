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
typedef  int /*<<< orphan*/  u32 ;
struct mmp_path {int /*<<< orphan*/  access_ok; } ;

/* Variables and functions */
 scalar_t__ LCD_SCLK (struct mmp_path*) ; 
 int /*<<< orphan*/  SCLK_DISABLE ; 
 scalar_t__ ctrl_regs (struct mmp_path*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void path_enabledisable(struct mmp_path *path, int on)
{
	u32 tmp;
	mutex_lock(&path->access_ok);
	tmp = readl_relaxed(ctrl_regs(path) + LCD_SCLK(path));
	if (on)
		tmp &= ~SCLK_DISABLE;
	else
		tmp |= SCLK_DISABLE;
	writel_relaxed(tmp, ctrl_regs(path) + LCD_SCLK(path));
	mutex_unlock(&path->access_ok);
}