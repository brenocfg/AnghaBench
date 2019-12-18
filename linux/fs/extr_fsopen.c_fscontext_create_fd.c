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

/* Variables and functions */
 unsigned int O_RDWR ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct fs_context*,unsigned int) ; 
 int /*<<< orphan*/  fscontext_fops ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 

__attribute__((used)) static int fscontext_create_fd(struct fs_context *fc, unsigned int o_flags)
{
	int fd;

	fd = anon_inode_getfd("[fscontext]", &fscontext_fops, fc,
			      O_RDWR | o_flags);
	if (fd < 0)
		put_fs_context(fc);
	return fd;
}