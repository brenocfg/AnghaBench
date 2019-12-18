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
typedef  scalar_t__ xa_mark_t ;
struct xa_state {int /*<<< orphan*/  xa; } ;

/* Variables and functions */
 scalar_t__ XA_FREE_MARK ; 
 scalar_t__ XA_MARK_MAX ; 
 int /*<<< orphan*/  mark_inc (scalar_t__) ; 
 scalar_t__ xa_track_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_clear_mark (struct xa_state const*,scalar_t__) ; 
 int /*<<< orphan*/  xas_set_mark (struct xa_state const*,scalar_t__) ; 

void xas_init_marks(const struct xa_state *xas)
{
	xa_mark_t mark = 0;

	for (;;) {
		if (xa_track_free(xas->xa) && mark == XA_FREE_MARK)
			xas_set_mark(xas, mark);
		else
			xas_clear_mark(xas, mark);
		if (mark == XA_MARK_MAX)
			break;
		mark_inc(mark);
	}
}