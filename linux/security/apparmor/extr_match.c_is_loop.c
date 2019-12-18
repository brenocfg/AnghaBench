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
struct match_workbuf {unsigned int pos; unsigned int* history; unsigned int len; unsigned int size; } ;

/* Variables and functions */

__attribute__((used)) static bool is_loop(struct match_workbuf *wb, unsigned int state,
		    unsigned int *adjust)
{
	unsigned int pos = wb->pos;
	unsigned int i;

	if (wb->history[pos] < state)
		return false;

	for (i = 0; i <= wb->len; i++) {
		if (wb->history[pos] == state) {
			*adjust = i;
			return true;
		}
		if (pos == 0)
			pos = wb->size;
		pos--;
	}

	*adjust = i;
	return true;
}