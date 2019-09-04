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

/* Variables and functions */
 unsigned long HZ ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cachefiles_create_histogram ; 
 int /*<<< orphan*/ * cachefiles_lookup_histogram ; 
 int /*<<< orphan*/ * cachefiles_mkdir_histogram ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int cachefiles_histogram_show(struct seq_file *m, void *v)
{
	unsigned long index;
	unsigned x, y, z, t;

	switch ((unsigned long) v) {
	case 1:
		seq_puts(m, "JIFS  SECS  LOOKUPS   MKDIRS    CREATES\n");
		return 0;
	case 2:
		seq_puts(m, "===== ===== ========= ========= =========\n");
		return 0;
	default:
		index = (unsigned long) v - 3;
		x = atomic_read(&cachefiles_lookup_histogram[index]);
		y = atomic_read(&cachefiles_mkdir_histogram[index]);
		z = atomic_read(&cachefiles_create_histogram[index]);
		if (x == 0 && y == 0 && z == 0)
			return 0;

		t = (index * 1000) / HZ;

		seq_printf(m, "%4lu  0.%03u %9u %9u %9u\n", index, t, x, y, z);
		return 0;
	}
}