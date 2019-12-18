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
typedef  scalar_t__ lfs2_block_t ;

/* Variables and functions */
 scalar_t__ const LFS2_BLOCK_NULL ; 

__attribute__((used)) static inline bool lfs2_pair_isnull(const lfs2_block_t pair[2]) {
    return pair[0] == LFS2_BLOCK_NULL || pair[1] == LFS2_BLOCK_NULL;
}