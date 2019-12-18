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
struct the_nilfs {int ns_blocks_per_segment; unsigned long ns_nrsvsegs; int /*<<< orphan*/  ns_ndirtyblks; int /*<<< orphan*/  ns_sufile; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long nilfs_sufile_get_ncleansegs (int /*<<< orphan*/ ) ; 

int nilfs_near_disk_full(struct the_nilfs *nilfs)
{
	unsigned long ncleansegs, nincsegs;

	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	nincsegs = atomic_read(&nilfs->ns_ndirtyblks) /
		nilfs->ns_blocks_per_segment + 1;

	return ncleansegs <= nilfs->ns_nrsvsegs + nincsegs;
}