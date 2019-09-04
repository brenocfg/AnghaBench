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
struct callchain_cursor {scalar_t__ pos; int /*<<< orphan*/  nr; int /*<<< orphan*/  curr; int /*<<< orphan*/  first; } ;

/* Variables and functions */

__attribute__((used)) static inline void callchain_cursor_snapshot(struct callchain_cursor *dest,
					     struct callchain_cursor *src)
{
	*dest = *src;

	dest->first = src->curr;
	dest->nr -= src->pos;
}