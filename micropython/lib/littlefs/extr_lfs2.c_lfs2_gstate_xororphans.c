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
typedef  int uint32_t ;
struct lfs2_gstate {int tag; } ;

/* Variables and functions */
 int LFS2_MKTAG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lfs2_gstate_xororphans(struct lfs2_gstate *a,
        const struct lfs2_gstate *b, bool orphans) {
    a->tag ^= LFS2_MKTAG(0x800, 0, 0) & (b->tag ^ ((uint32_t)orphans << 31));
}