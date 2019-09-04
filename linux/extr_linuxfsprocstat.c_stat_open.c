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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int nr_irqs ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  show_stat ; 
 int single_open_size (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int stat_open(struct inode *inode, struct file *file)
{
	unsigned int size = 1024 + 128 * num_online_cpus();

	/* minimum size to display an interrupt count : 2 bytes */
	size += 2 * nr_irqs;
	return single_open_size(file, show_stat, NULL, size);
}