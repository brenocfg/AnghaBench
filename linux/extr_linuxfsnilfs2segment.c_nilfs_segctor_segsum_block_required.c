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
struct nilfs_segsum_pointer {unsigned int offset; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_blk_cnt; TYPE_1__* sc_super; } ;
struct nilfs_finfo {int dummy; } ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static int nilfs_segctor_segsum_block_required(
	struct nilfs_sc_info *sci, const struct nilfs_segsum_pointer *ssp,
	unsigned int binfo_size)
{
	unsigned int blocksize = sci->sc_super->s_blocksize;
	/* Size of finfo and binfo is enough small against blocksize */

	return ssp->offset + binfo_size +
		(!sci->sc_blk_cnt ? sizeof(struct nilfs_finfo) : 0) >
		blocksize;
}