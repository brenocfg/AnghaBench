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
typedef  scalar_t__ u32 ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_block_group_reasonably_empty(struct ocfs2_group_desc *bg,
						     u32 wanted)
{
	return le16_to_cpu(bg->bg_free_bits_count) > wanted;
}