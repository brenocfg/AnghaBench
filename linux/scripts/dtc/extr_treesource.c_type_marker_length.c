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
struct marker {size_t offset; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct marker* next_type_marker (int /*<<< orphan*/ ) ; 

size_t type_marker_length(struct marker *m)
{
	struct marker *next = next_type_marker(m->next);

	if (next)
		return next->offset - m->offset;
	return 0;
}