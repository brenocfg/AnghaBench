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
struct TYPE_2__ {int /*<<< orphan*/  period_in_ps; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int /*<<< orphan*/  u32 ;
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 aty_pll_8398_to_var(const struct fb_info *info,
			       const union aty_pll *pll)
{
	return (pll->ics2595.period_in_ps);	/* default for now */
}