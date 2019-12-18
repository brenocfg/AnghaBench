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
struct marker {struct marker* ref; struct marker* next; } ;
struct data {struct marker* val; struct marker* markers; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct marker*) ; 

void data_free(struct data d)
{
	struct marker *m, *nm;

	m = d.markers;
	while (m) {
		nm = m->next;
		free(m->ref);
		free(m);
		m = nm;
	}

	if (d.val)
		free(d.val);
}