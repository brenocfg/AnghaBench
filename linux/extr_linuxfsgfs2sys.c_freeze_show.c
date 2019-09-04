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
struct TYPE_2__ {int /*<<< orphan*/  frozen; } ;
struct super_block {TYPE_1__ s_writers; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SB_UNFROZEN ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t freeze_show(struct gfs2_sbd *sdp, char *buf)
{
	struct super_block *sb = sdp->sd_vfs;
	int frozen = (sb->s_writers.frozen == SB_UNFROZEN) ? 0 : 1;

	return snprintf(buf, PAGE_SIZE, "%d\n", frozen);
}