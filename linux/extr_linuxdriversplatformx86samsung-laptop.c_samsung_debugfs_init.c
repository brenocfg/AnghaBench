#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; TYPE_2__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  d3; int /*<<< orphan*/  d2; int /*<<< orphan*/  d1; int /*<<< orphan*/  d0; } ;
struct TYPE_4__ {TYPE_3__ sdiag_wrapper; int /*<<< orphan*/  root; TYPE_3__ f0000_wrapper; TYPE_3__ data_wrapper; TYPE_2__ data; int /*<<< orphan*/  command; } ;
struct samsung_laptop {TYPE_1__ debug; TYPE_2__* sdiag; TYPE_2__* f0000_segment; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_blob (char*,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct samsung_laptop*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u16 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  samsung_debugfs_exit (struct samsung_laptop*) ; 
 int /*<<< orphan*/  samsung_laptop_call_fops ; 
 int strlen (TYPE_2__*) ; 

__attribute__((used)) static int samsung_debugfs_init(struct samsung_laptop *samsung)
{
	struct dentry *dent;

	samsung->debug.root = debugfs_create_dir("samsung-laptop", NULL);
	if (!samsung->debug.root) {
		pr_err("failed to create debugfs directory");
		goto error_debugfs;
	}

	samsung->debug.f0000_wrapper.data = samsung->f0000_segment;
	samsung->debug.f0000_wrapper.size = 0xffff;

	samsung->debug.data_wrapper.data = &samsung->debug.data;
	samsung->debug.data_wrapper.size = sizeof(samsung->debug.data);

	samsung->debug.sdiag_wrapper.data = samsung->sdiag;
	samsung->debug.sdiag_wrapper.size = strlen(samsung->sdiag);

	dent = debugfs_create_u16("command", S_IRUGO | S_IWUSR,
				  samsung->debug.root, &samsung->debug.command);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_u32("d0", S_IRUGO | S_IWUSR, samsung->debug.root,
				  &samsung->debug.data.d0);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_u32("d1", S_IRUGO | S_IWUSR, samsung->debug.root,
				  &samsung->debug.data.d1);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_u16("d2", S_IRUGO | S_IWUSR, samsung->debug.root,
				  &samsung->debug.data.d2);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_u8("d3", S_IRUGO | S_IWUSR, samsung->debug.root,
				 &samsung->debug.data.d3);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_blob("data", S_IRUGO | S_IWUSR,
				   samsung->debug.root,
				   &samsung->debug.data_wrapper);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_blob("f0000_segment", S_IRUSR | S_IWUSR,
				   samsung->debug.root,
				   &samsung->debug.f0000_wrapper);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_file("call", S_IFREG | S_IRUGO,
				   samsung->debug.root, samsung,
				   &samsung_laptop_call_fops);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_blob("sdiag", S_IRUGO | S_IWUSR,
				   samsung->debug.root,
				   &samsung->debug.sdiag_wrapper);
	if (!dent)
		goto error_debugfs;

	return 0;

error_debugfs:
	samsung_debugfs_exit(samsung);
	return -ENOMEM;
}