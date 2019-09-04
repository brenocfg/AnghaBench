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
struct rb_node {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* rb_next (struct rb_node*) ; 

__attribute__((used)) static void *nommu_region_list_next(struct seq_file *m, void *v, loff_t *pos)
{
	(*pos)++;
	return rb_next((struct rb_node *) v);
}