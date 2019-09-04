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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FREE_SPACE (struct buffer_head*) ; 
 int /*<<< orphan*/  B_LEVEL (struct buffer_head*) ; 
 int /*<<< orphan*/  B_NR_ITEMS (struct buffer_head*) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scnprintf_block_head(char *buf, size_t size, struct buffer_head *bh)
{
	return scnprintf(buf, size,
			 "level=%d, nr_items=%d, free_space=%d rdkey ",
			 B_LEVEL(bh), B_NR_ITEMS(bh), B_FREE_SPACE(bh));
}