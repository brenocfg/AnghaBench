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
struct f2fs_extent {void* len; void* blk; void* fofs; } ;
struct extent_info {int /*<<< orphan*/  len; int /*<<< orphan*/  blk; int /*<<< orphan*/  fofs; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_raw_extent(struct extent_info *ext,
					struct f2fs_extent *i_ext)
{
	i_ext->fofs = cpu_to_le32(ext->fofs);
	i_ext->blk = cpu_to_le32(ext->blk);
	i_ext->len = cpu_to_le32(ext->len);
}