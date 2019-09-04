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
struct fuse_conn {int /*<<< orphan*/  killsb; int /*<<< orphan*/ * sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_abort_conn (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_send_destroy (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_wait_aborted (struct fuse_conn*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_sb_destroy(struct super_block *sb)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);

	if (fc) {
		fuse_send_destroy(fc);

		fuse_abort_conn(fc, false);
		fuse_wait_aborted(fc);

		down_write(&fc->killsb);
		fc->sb = NULL;
		up_write(&fc->killsb);
	}
}