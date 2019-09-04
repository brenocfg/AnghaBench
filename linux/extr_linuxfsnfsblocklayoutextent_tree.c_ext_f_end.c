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
struct pnfs_block_extent {scalar_t__ be_length; scalar_t__ be_f_offset; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static inline sector_t
ext_f_end(struct pnfs_block_extent *be)
{
	return be->be_f_offset + be->be_length;
}