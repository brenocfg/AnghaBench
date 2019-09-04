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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ has_osd_alpha; } ;
struct s3c_fb_win {int /*<<< orphan*/  index; TYPE_1__ variant; struct s3c_fb* parent; } ;
struct s3c_fb {int /*<<< orphan*/  variant; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ VIDOSD_C (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vidosd_set_alpha(struct s3c_fb_win *win, u32 alpha)
{
	struct s3c_fb *sfb = win->parent;

	if (win->variant.has_osd_alpha)
		writel(alpha, sfb->regs + VIDOSD_C(win->index, sfb->variant));
}