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
struct SN_env {int bra; int c; int l; int* p; int ket; int* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_9 ; 
 int /*<<< orphan*/  find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int*) ; 
 int /*<<< orphan*/  s_67 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Prefix_Step4_Verb(struct SN_env * z) { /* forwardmode */
    z->bra = z->c; /* [, line 402 */
    if (z->c + 5 >= z->l || z->p[z->c + 5] != 170) return 0; /* substring, line 402 */
    if (!(find_among(z, a_9, 3))) return 0;
    z->ket = z->c; /* ], line 402 */
    if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 403 */
    z->B[1] = 1; /* set is_verb, line 403 */
    z->B[0] = 0; /* unset is_noun, line 403 */
    {   int ret = slice_from_s(z, 6, s_67); /* <-, line 403 */
        if (ret < 0) return ret;
    }
    return 1;
}