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
struct seq_file {struct map_iter* private; } ;
struct map_iter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct map_iter *map_iter(struct seq_file *m)
{
	return m->private;
}