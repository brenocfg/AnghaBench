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
typedef  int loff_t ;

/* Variables and functions */
 int TAPE_MINORS_PER_DEV ; 

__attribute__((used)) static void *tape_proc_start(struct seq_file *m, loff_t *pos)
{
	if (*pos >= 256 / TAPE_MINORS_PER_DEV)
		return NULL;
	return (void *)((unsigned long) *pos + 1);
}