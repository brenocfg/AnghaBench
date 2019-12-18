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
typedef  int /*<<< orphan*/  lfs1_block_t ;

/* Variables and functions */

__attribute__((used)) static inline void lfs1_pairswap(lfs1_block_t pair[2]) {
    lfs1_block_t t = pair[0];
    pair[0] = pair[1];
    pair[1] = t;
}