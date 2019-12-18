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
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_10 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_fix_gd(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 345 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] != 100) return 0; /* substring, line 345 */
    if (!(find_among_b(z, a_4, 1))) return 0;
    z->bra = z->c; /* ], line 345 */
    {   int ret = slice_from_s(z, 1, s_10); /* <-, line 346 */
        if (ret < 0) return ret;
    }
    return 1;
}