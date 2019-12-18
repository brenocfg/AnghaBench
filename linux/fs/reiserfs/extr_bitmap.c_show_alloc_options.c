#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct seq_file {int dummy; } ;
struct TYPE_3__ {int border; int large_file_size; int preallocmin; int preallocsize; } ;
struct TYPE_4__ {TYPE_1__ s_alloc_options; } ;

/* Variables and functions */
 TYPE_2__* REISERFS_SB (struct super_block*) ; 
 int SB_ALLOC_OPTS (struct super_block*) ; 
 scalar_t__ TEST_OPTION (int /*<<< orphan*/ ,struct super_block*) ; 
 int _ALLOC_dirid_groups ; 
 int _ALLOC_packing_groups ; 
 int _ALLOC_skip_busy ; 
 int /*<<< orphan*/  concentrating_formatted_nodes ; 
 int /*<<< orphan*/  dirid_groups ; 
 int /*<<< orphan*/  displace_based_on_dirid ; 
 int /*<<< orphan*/  displacing_large_files ; 
 int /*<<< orphan*/  displacing_new_packing_localities ; 
 int /*<<< orphan*/  hashed_formatted_nodes ; 
 int /*<<< orphan*/  hundredth_slices ; 
 int /*<<< orphan*/  new_hashed_relocation ; 
 int /*<<< orphan*/  oid_groups ; 
 int /*<<< orphan*/  old_hashed_relocation ; 
 int /*<<< orphan*/  old_way ; 
 int /*<<< orphan*/  packing_groups ; 
 int /*<<< orphan*/  print_sep (struct seq_file*,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  skip_busy ; 

void show_alloc_options(struct seq_file *seq, struct super_block *s)
{
	int first = 1;

	if (SB_ALLOC_OPTS(s) == ((1 << _ALLOC_skip_busy) |
		(1 << _ALLOC_dirid_groups) | (1 << _ALLOC_packing_groups)))
		return;

	seq_puts(seq, ",alloc=");

	if (TEST_OPTION(concentrating_formatted_nodes, s)) {
		print_sep(seq, &first);
		if (REISERFS_SB(s)->s_alloc_options.border != 10) {
			seq_printf(seq, "concentrating_formatted_nodes=%d",
				100 / REISERFS_SB(s)->s_alloc_options.border);
		} else
			seq_puts(seq, "concentrating_formatted_nodes");
	}
	if (TEST_OPTION(displacing_large_files, s)) {
		print_sep(seq, &first);
		if (REISERFS_SB(s)->s_alloc_options.large_file_size != 16) {
			seq_printf(seq, "displacing_large_files=%lu",
			    REISERFS_SB(s)->s_alloc_options.large_file_size);
		} else
			seq_puts(seq, "displacing_large_files");
	}
	if (TEST_OPTION(displacing_new_packing_localities, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "displacing_new_packing_localities");
	}
	if (TEST_OPTION(old_hashed_relocation, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "old_hashed_relocation");
	}
	if (TEST_OPTION(new_hashed_relocation, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "new_hashed_relocation");
	}
	if (TEST_OPTION(dirid_groups, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "dirid_groups");
	}
	if (TEST_OPTION(oid_groups, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "oid_groups");
	}
	if (TEST_OPTION(packing_groups, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "packing_groups");
	}
	if (TEST_OPTION(hashed_formatted_nodes, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "hashed_formatted_nodes");
	}
	if (TEST_OPTION(skip_busy, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "skip_busy");
	}
	if (TEST_OPTION(hundredth_slices, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "hundredth_slices");
	}
	if (TEST_OPTION(old_way, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "old_way");
	}
	if (TEST_OPTION(displace_based_on_dirid, s)) {
		print_sep(seq, &first);
		seq_puts(seq, "displace_based_on_dirid");
	}
	if (REISERFS_SB(s)->s_alloc_options.preallocmin != 0) {
		print_sep(seq, &first);
		seq_printf(seq, "preallocmin=%d",
				REISERFS_SB(s)->s_alloc_options.preallocmin);
	}
	if (REISERFS_SB(s)->s_alloc_options.preallocsize != 17) {
		print_sep(seq, &first);
		seq_printf(seq, "preallocsize=%d",
				REISERFS_SB(s)->s_alloc_options.preallocsize);
	}
}