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

/* Variables and functions */
 int /*<<< orphan*/  allocated_irqs ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free_desc (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int nr_irqs ; 
 int /*<<< orphan*/  sparse_irq_lock ; 

void irq_free_descs(unsigned int from, unsigned int cnt)
{
	int i;

	if (from >= nr_irqs || (from + cnt) > nr_irqs)
		return;

	mutex_lock(&sparse_irq_lock);
	for (i = 0; i < cnt; i++)
		free_desc(from + i);

	bitmap_clear(allocated_irqs, from, cnt);
	mutex_unlock(&sparse_irq_lock);
}