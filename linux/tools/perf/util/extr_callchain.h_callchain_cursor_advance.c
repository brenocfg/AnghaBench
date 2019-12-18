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
struct callchain_cursor {int /*<<< orphan*/  pos; TYPE_1__* curr; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void callchain_cursor_advance(struct callchain_cursor *cursor)
{
	cursor->curr = cursor->curr->next;
	cursor->pos++;
}