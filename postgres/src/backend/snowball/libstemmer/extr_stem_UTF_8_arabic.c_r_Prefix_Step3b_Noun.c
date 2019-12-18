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
struct SN_env {int c; int bra; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_7 ; 
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int*) ; 
 int /*<<< orphan*/  s_60 ; 
 int /*<<< orphan*/  s_61 ; 
 int /*<<< orphan*/  s_62 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Prefix_Step3b_Noun(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c1 = z->c; /* not, line 381 */
        if (!(eq_s(z, 4, s_60))) goto lab0; /* literal, line 381 */
        return 0;
    lab0:
        z->c = c1;
    }
    z->bra = z->c; /* [, line 382 */
    if (z->c + 1 >= z->l || (z->p[z->c + 1] != 168 && z->p[z->c + 1] != 131)) return 0; /* substring, line 382 */
    among_var = find_among(z, a_7, 3);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 382 */
    switch (among_var) { /* among, line 382 */
        case 1:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 383 */
            {   int ret = slice_del(z); /* delete, line 383 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 385 */
            {   int ret = slice_from_s(z, 2, s_61); /* <-, line 385 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 386 */
            {   int ret = slice_from_s(z, 2, s_62); /* <-, line 386 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}