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
struct TYPE_2__ {int /*<<< orphan*/  ffs_fc_hist; } ;
struct ocfs2_info_freefrag {TYPE_1__ iff_ffs; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2ffg_update_histogram (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  o2ffg_update_stats (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void ocfs2_info_update_ffg(struct ocfs2_info_freefrag *ffg,
				  unsigned int chunksize)
{
	o2ffg_update_histogram(&(ffg->iff_ffs.ffs_fc_hist), chunksize);
	o2ffg_update_stats(&(ffg->iff_ffs), chunksize);
}