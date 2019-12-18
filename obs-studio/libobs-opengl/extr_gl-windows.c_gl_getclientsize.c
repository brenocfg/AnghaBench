#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_swap_chain {TYPE_1__* wi; } ;
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_2__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 

extern void gl_getclientsize(const struct gs_swap_chain *swap, uint32_t *width,
			     uint32_t *height)
{
	RECT rc;
	if (swap) {
		GetClientRect(swap->wi->hwnd, &rc);
		*width = rc.right;
		*height = rc.bottom;
	} else {
		*width = 0;
		*height = 0;
	}
}