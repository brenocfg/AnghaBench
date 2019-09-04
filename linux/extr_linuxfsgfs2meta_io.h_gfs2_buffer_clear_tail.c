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
struct buffer_head {int b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gfs2_buffer_clear_tail(struct buffer_head *bh, int head)
{
	BUG_ON(head > bh->b_size);
	memset(bh->b_data + head, 0, bh->b_size - head);
}