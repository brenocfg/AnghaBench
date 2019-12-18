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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_21 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_68 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Suffix_All_alef_maqsura(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 483 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] != 137) return 0; /* substring, line 483 */
    if (!(find_among_b(z, a_21, 1))) return 0;
    z->bra = z->c; /* ], line 483 */
    {   int ret = slice_from_s(z, 2, s_68); /* <-, line 484 */
        if (ret < 0) return ret;
    }
    return 1;
}