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
typedef  int /*<<< orphan*/  lfs2_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_fromle32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lfs2_pair_fromle32(lfs2_block_t pair[2]) {
    pair[0] = lfs2_fromle32(pair[0]);
    pair[1] = lfs2_fromle32(pair[1]);
}