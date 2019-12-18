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
typedef  int /*<<< orphan*/  umode_t ;
struct dentry {int dummy; } ;
struct debugfs_blob_wrapper {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_file_unsafe (char const*,int /*<<< orphan*/ ,struct dentry*,struct debugfs_blob_wrapper*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_blob ; 

struct dentry *debugfs_create_blob(const char *name, umode_t mode,
				   struct dentry *parent,
				   struct debugfs_blob_wrapper *blob)
{
	return debugfs_create_file_unsafe(name, mode, parent, blob, &fops_blob);
}