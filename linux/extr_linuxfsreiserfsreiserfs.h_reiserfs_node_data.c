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
struct buffer_head {void* b_data; } ;
struct block_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void *reiserfs_node_data(const struct buffer_head *bh)
{
	return bh->b_data + sizeof(struct block_head);
}