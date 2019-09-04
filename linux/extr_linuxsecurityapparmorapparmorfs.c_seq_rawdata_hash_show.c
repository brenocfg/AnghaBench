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
struct seq_file {struct aa_loaddata* private; } ;
struct aa_loaddata {int /*<<< orphan*/ * hash; } ;

/* Variables and functions */
 unsigned int aa_hash_size () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int seq_rawdata_hash_show(struct seq_file *seq, void *v)
{
	struct aa_loaddata *data = seq->private;
	unsigned int i, size = aa_hash_size();

	if (data->hash) {
		for (i = 0; i < size; i++)
			seq_printf(seq, "%.2x", data->hash[i]);
		seq_putc(seq, '\n');
	}

	return 0;
}