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
struct SN_env {int* B; int bra; int c; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_11 ; 
 int /*<<< orphan*/  a_12 ; 
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_fix_va_start (struct SN_env*) ; 
 int /*<<< orphan*/  s_45 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_remove_pronoun_prefixes(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset found_a_match, line 161 */
    z->bra = z->c; /* [, line 162 */
    if (z->c + 2 >= z->l || z->p[z->c + 2] >> 5 != 4 || !((672 >> (z->p[z->c + 2] & 0x1f)) & 1)) return 0; /* among, line 162 */
    if (!(find_among(z, a_11, 3))) return 0;
    if (!(find_among(z, a_12, 10))) return 0; /* among, line 162 */
    if (!(eq_s(z, 3, s_45))) return 0; /* literal, line 162 */
    z->ket = z->c; /* ], line 162 */
    {   int ret = slice_del(z); /* delete, line 162 */
        if (ret < 0) return ret;
    }
    z->B[0] = 1; /* set found_a_match, line 163 */
    {   int c1 = z->c; /* do, line 164 */
        {   int ret = r_fix_va_start(z); /* call fix_va_start, line 164 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    return 1;
}