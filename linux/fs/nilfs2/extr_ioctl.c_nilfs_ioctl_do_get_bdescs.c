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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_dat; } ;
struct nilfs_bmap {int dummy; } ;
struct nilfs_bdesc {scalar_t__ bd_blocknr; scalar_t__ bd_level; int /*<<< orphan*/  bd_offset; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {struct nilfs_bmap* i_bmap; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* NILFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int nilfs_bmap_lookup_at_level (struct nilfs_bmap*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_ioctl_do_get_bdescs(struct the_nilfs *nilfs, __u64 *posp, int flags,
			  void *buf, size_t size, size_t nmembs)
{
	struct nilfs_bmap *bmap = NILFS_I(nilfs->ns_dat)->i_bmap;
	struct nilfs_bdesc *bdescs = buf;
	int ret, i;

	down_read(&nilfs->ns_segctor_sem);
	for (i = 0; i < nmembs; i++) {
		ret = nilfs_bmap_lookup_at_level(bmap,
						 bdescs[i].bd_offset,
						 bdescs[i].bd_level + 1,
						 &bdescs[i].bd_blocknr);
		if (ret < 0) {
			if (ret != -ENOENT) {
				up_read(&nilfs->ns_segctor_sem);
				return ret;
			}
			bdescs[i].bd_blocknr = 0;
		}
	}
	up_read(&nilfs->ns_segctor_sem);
	return nmembs;
}