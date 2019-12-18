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
typedef  int u64 ;
typedef  int blkcnt_t ;

/* Variables and functions */

__attribute__((used)) static inline blkcnt_t calc_inode_blocks(u64 size)
{
	return (size + (1<<9) - 1) >> 9;
}