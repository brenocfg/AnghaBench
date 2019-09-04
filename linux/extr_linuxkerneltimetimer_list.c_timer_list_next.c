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
struct timer_list_iter {int dummy; } ;
struct seq_file {struct timer_list_iter* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* move_iter (struct timer_list_iter*,int) ; 

__attribute__((used)) static void *timer_list_next(struct seq_file *file, void *v, loff_t *offset)
{
	struct timer_list_iter *iter = file->private;
	++*offset;
	return move_iter(iter, 1);
}