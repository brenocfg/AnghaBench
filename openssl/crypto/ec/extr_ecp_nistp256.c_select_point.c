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
typedef  unsigned int u64 ;
typedef  unsigned int* smallfelem ;

/* Variables and functions */
 int NLIMBS ; 
 int /*<<< orphan*/  memset (unsigned int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void select_point(const u64 idx, unsigned int size,
                         const smallfelem pre_comp[16][3], smallfelem out[3])
{
    unsigned i, j;
    u64 *outlimbs = &out[0][0];

    memset(out, 0, sizeof(*out) * 3);

    for (i = 0; i < size; i++) {
        const u64 *inlimbs = (u64 *)&pre_comp[i][0][0];
        u64 mask = i ^ idx;
        mask |= mask >> 4;
        mask |= mask >> 2;
        mask |= mask >> 1;
        mask &= 1;
        mask--;
        for (j = 0; j < NLIMBS * 3; j++)
            outlimbs[j] |= inlimbs[j] & mask;
    }
}