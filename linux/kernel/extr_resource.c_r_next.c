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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ next_resource (struct resource*,int) ; 

__attribute__((used)) static void *r_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct resource *p = v;
	(*pos)++;
	return (void *)next_resource(p, false);
}