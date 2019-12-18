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
struct nilfs_sc_info {int /*<<< orphan*/  sc_dsync_end; int /*<<< orphan*/  sc_dsync_start; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_buffers ; 
 int /*<<< orphan*/  nilfs_collect_file_data ; 
 size_t nilfs_lookup_dirty_data_buffers (struct inode*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nilfs_segctor_apply_buffers (struct nilfs_sc_info*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t nilfs_segctor_buffer_rest (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_end_finfo (struct nilfs_sc_info*,struct inode*) ; 

__attribute__((used)) static int nilfs_segctor_scan_file_dsync(struct nilfs_sc_info *sci,
					 struct inode *inode)
{
	LIST_HEAD(data_buffers);
	size_t n, rest = nilfs_segctor_buffer_rest(sci);
	int err;

	n = nilfs_lookup_dirty_data_buffers(inode, &data_buffers, rest + 1,
					    sci->sc_dsync_start,
					    sci->sc_dsync_end);

	err = nilfs_segctor_apply_buffers(sci, inode, &data_buffers,
					  nilfs_collect_file_data);
	if (!err) {
		nilfs_segctor_end_finfo(sci, inode);
		BUG_ON(n > rest);
		/* always receive -E2BIG or true error if n > rest */
	}
	return err;
}