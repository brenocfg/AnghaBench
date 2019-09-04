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
struct the_nilfs {int ns_blocks_per_segment; int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_sufile; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned long nilfs_sufile_get_ncleansegs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_count_free_blocks(struct the_nilfs *nilfs, sector_t *nblocks)
{
	unsigned long ncleansegs;

	down_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	up_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	*nblocks = (sector_t)ncleansegs * nilfs->ns_blocks_per_segment;
	return 0;
}