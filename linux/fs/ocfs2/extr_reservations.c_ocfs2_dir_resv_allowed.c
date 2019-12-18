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
struct ocfs2_super {scalar_t__ osb_dir_resv_level; scalar_t__ osb_resv_level; } ;

/* Variables and functions */

int ocfs2_dir_resv_allowed(struct ocfs2_super *osb)
{
	return (osb->osb_resv_level && osb->osb_dir_resv_level);
}