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
struct super_block {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  no_force_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_abort_conn (struct fuse_conn*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 

__attribute__((used)) static void fuse_umount_begin(struct super_block *sb)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);

	if (!fc->no_force_umount)
		fuse_abort_conn(fc);
}