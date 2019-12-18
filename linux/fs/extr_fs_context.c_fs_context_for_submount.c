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
struct fs_context {int dummy; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_CONTEXT_FOR_SUBMOUNT ; 
 struct fs_context* alloc_fs_context (struct file_system_type*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fs_context *fs_context_for_submount(struct file_system_type *type,
					   struct dentry *reference)
{
	return alloc_fs_context(type, reference, 0, 0, FS_CONTEXT_FOR_SUBMOUNT);
}