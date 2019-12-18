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
typedef  scalar_t__ u64 ;
struct ocfs2_suballoc_result {scalar_t__ sr_blkno; int /*<<< orphan*/  sr_bit_offset; scalar_t__ sr_bg_blkno; } ;

/* Variables and functions */
 scalar_t__ ocfs2_which_suballoc_group (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ocfs2_group_from_res(struct ocfs2_suballoc_result *res)
{
	if (res->sr_blkno == 0)
		return 0;

	if (res->sr_bg_blkno)
		return res->sr_bg_blkno;

	return ocfs2_which_suballoc_group(res->sr_blkno, res->sr_bit_offset);
}