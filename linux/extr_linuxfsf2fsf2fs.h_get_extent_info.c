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
struct f2fs_extent {int /*<<< orphan*/  len; int /*<<< orphan*/  blk; int /*<<< orphan*/  fofs; } ;
struct extent_info {void* len; void* blk; void* fofs; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void get_extent_info(struct extent_info *ext,
					struct f2fs_extent *i_ext)
{
	ext->fofs = le32_to_cpu(i_ext->fofs);
	ext->blk = le32_to_cpu(i_ext->blk);
	ext->len = le32_to_cpu(i_ext->len);
}