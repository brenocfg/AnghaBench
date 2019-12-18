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
struct ocfs2_slot_info {scalar_t__ si_extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_update_slot_info_extended (struct ocfs2_slot_info*) ; 
 int /*<<< orphan*/  ocfs2_update_slot_info_old (struct ocfs2_slot_info*) ; 

__attribute__((used)) static void ocfs2_update_slot_info(struct ocfs2_slot_info *si)
{
	/*
	 * The slot data will have been refreshed when ocfs2_super_lock
	 * was taken.
	 */
	if (si->si_extended)
		ocfs2_update_slot_info_extended(si);
	else
		ocfs2_update_slot_info_old(si);
}