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
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ nfs_ctx_key_to_expire (struct nfs_open_context*,struct inode*) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 

__attribute__((used)) static int nfs_need_check_write(struct file *filp, struct inode *inode)
{
	struct nfs_open_context *ctx;

	ctx = nfs_file_open_context(filp);
	if (nfs_ctx_key_to_expire(ctx, inode))
		return 1;
	return 0;
}