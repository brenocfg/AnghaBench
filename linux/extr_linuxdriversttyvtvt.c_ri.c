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
struct vc_data {scalar_t__ vc_y; scalar_t__ vc_top; scalar_t__ vc_need_wrap; scalar_t__ vc_size_row; int /*<<< orphan*/  vc_pos; int /*<<< orphan*/  vc_bottom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM_DOWN ; 
 int /*<<< orphan*/  con_scroll (struct vc_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ri(struct vc_data *vc)
{
    	/* don't scroll if below top of scrolling region, or
	 * if above scrolling region
	 */
	if (vc->vc_y == vc->vc_top)
		con_scroll(vc, vc->vc_top, vc->vc_bottom, SM_DOWN, 1);
	else if (vc->vc_y > 0) {
		vc->vc_y--;
		vc->vc_pos -= vc->vc_size_row;
	}
	vc->vc_need_wrap = 0;
}