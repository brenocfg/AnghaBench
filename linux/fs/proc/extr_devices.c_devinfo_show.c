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
 int CHRDEV_MAJOR_MAX ; 
 int /*<<< orphan*/  blkdev_show (struct seq_file*,int) ; 
 int /*<<< orphan*/  chrdev_show (struct seq_file*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int devinfo_show(struct seq_file *f, void *v)
{
	int i = *(loff_t *) v;

	if (i < CHRDEV_MAJOR_MAX) {
		if (i == 0)
			seq_puts(f, "Character devices:\n");
		chrdev_show(f, i);
	}
#ifdef CONFIG_BLOCK
	else {
		i -= CHRDEV_MAJOR_MAX;
		if (i == 0)
			seq_puts(f, "\nBlock devices:\n");
		blkdev_show(f, i);
	}
#endif
	return 0;
}