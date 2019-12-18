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
typedef  int const* smallfelem ;
typedef  int limb ;
typedef  int* felem ;

/* Variables and functions */
 unsigned int NLIMBS ; 

__attribute__((used)) static void copy_small_conditional(felem out, const smallfelem in, limb mask)
{
    unsigned i;
    const u64 mask64 = mask;
    for (i = 0; i < NLIMBS; ++i) {
        out[i] = ((limb) (in[i] & mask64)) | (out[i] & ~mask);
    }
}