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
struct aa_loaddata {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_rawdata_revision_show(struct seq_file *seq, void *v)
{
	struct aa_loaddata *data = seq->private;

	seq_printf(seq, "%ld\n", data->revision);

	return 0;
}