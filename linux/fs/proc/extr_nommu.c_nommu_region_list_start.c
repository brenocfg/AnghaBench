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
struct seq_file {int dummy; } ;
typedef  void rb_node ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nommu_region_sem ; 
 int /*<<< orphan*/  nommu_region_tree ; 
 void* rb_first (int /*<<< orphan*/ *) ; 
 void* rb_next (void*) ; 

__attribute__((used)) static void *nommu_region_list_start(struct seq_file *m, loff_t *_pos)
{
	struct rb_node *p;
	loff_t pos = *_pos;

	down_read(&nommu_region_sem);

	for (p = rb_first(&nommu_region_tree); p; p = rb_next(p))
		if (pos-- == 0)
			return p;
	return NULL;
}