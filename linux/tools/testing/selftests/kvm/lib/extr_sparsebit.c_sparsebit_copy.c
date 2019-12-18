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
struct sparsebit {int /*<<< orphan*/  num_set; scalar_t__ root; } ;

/* Variables and functions */
 scalar_t__ node_copy_subtree (scalar_t__) ; 
 int /*<<< orphan*/  sparsebit_clear_all (struct sparsebit*) ; 

void sparsebit_copy(struct sparsebit *d, struct sparsebit *s)
{
	/* First clear any bits already set in the destination */
	sparsebit_clear_all(d);

	if (s->root) {
		d->root = node_copy_subtree(s->root);
		d->num_set = s->num_set;
	}
}