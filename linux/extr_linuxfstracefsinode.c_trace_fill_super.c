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
struct tree_descr {char* member_0; } ;
struct tracefs_fs_info {int /*<<< orphan*/  mount_opts; } ;
struct super_block {struct tracefs_fs_info* s_fs_info; int /*<<< orphan*/ * s_op; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACEFS_MAGIC ; 
 int /*<<< orphan*/  kfree (struct tracefs_fs_info*) ; 
 struct tracefs_fs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int simple_fill_super (struct super_block*,int /*<<< orphan*/ ,struct tree_descr const*) ; 
 int /*<<< orphan*/  tracefs_apply_options (struct super_block*) ; 
 int tracefs_parse_options (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracefs_super_operations ; 

__attribute__((used)) static int trace_fill_super(struct super_block *sb, void *data, int silent)
{
	static const struct tree_descr trace_files[] = {{""}};
	struct tracefs_fs_info *fsi;
	int err;

	fsi = kzalloc(sizeof(struct tracefs_fs_info), GFP_KERNEL);
	sb->s_fs_info = fsi;
	if (!fsi) {
		err = -ENOMEM;
		goto fail;
	}

	err = tracefs_parse_options(data, &fsi->mount_opts);
	if (err)
		goto fail;

	err  =  simple_fill_super(sb, TRACEFS_MAGIC, trace_files);
	if (err)
		goto fail;

	sb->s_op = &tracefs_super_operations;

	tracefs_apply_options(sb);

	return 0;

fail:
	kfree(fsi);
	sb->s_fs_info = NULL;
	return err;
}