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
struct super_block {int dummy; } ;

/* Variables and functions */
 int ocfs2_extent_recs_per_gd (struct super_block*) ; 

__attribute__((used)) static inline int ocfs2_calc_bg_discontig_credits(struct super_block *sb)
{
	return ocfs2_extent_recs_per_gd(sb);
}