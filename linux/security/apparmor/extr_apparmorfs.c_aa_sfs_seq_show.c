#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct aa_sfs_entry* private; } ;
struct TYPE_2__ {char* string; char* u64; int /*<<< orphan*/  boolean; } ;
struct aa_sfs_entry {int v_type; TYPE_1__ v; } ;

/* Variables and functions */
#define  AA_SFS_TYPE_BOOLEAN 130 
#define  AA_SFS_TYPE_STRING 129 
#define  AA_SFS_TYPE_U64 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int aa_sfs_seq_show(struct seq_file *seq, void *v)
{
	struct aa_sfs_entry *fs_file = seq->private;

	if (!fs_file)
		return 0;

	switch (fs_file->v_type) {
	case AA_SFS_TYPE_BOOLEAN:
		seq_printf(seq, "%s\n", fs_file->v.boolean ? "yes" : "no");
		break;
	case AA_SFS_TYPE_STRING:
		seq_printf(seq, "%s\n", fs_file->v.string);
		break;
	case AA_SFS_TYPE_U64:
		seq_printf(seq, "%#08lx\n", fs_file->v.u64);
		break;
	default:
		/* Ignore unpritable entry types. */
		break;
	}

	return 0;
}