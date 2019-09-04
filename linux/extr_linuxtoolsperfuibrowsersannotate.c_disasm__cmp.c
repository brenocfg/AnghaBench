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
struct annotation_line {int data_nr; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ percent; } ;

/* Variables and functions */

__attribute__((used)) static int disasm__cmp(struct annotation_line *a, struct annotation_line *b)
{
	int i;

	for (i = 0; i < a->data_nr; i++) {
		if (a->data[i].percent == b->data[i].percent)
			continue;
		return a->data[i].percent < b->data[i].percent;
	}
	return 0;
}