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
struct SN_env {int l; int c; int ket; int lb; int* p; size_t bra; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_45 ; 
 int /*<<< orphan*/  a_46 ; 
 int /*<<< orphan*/  a_47 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v2 ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_80 ; 
 int /*<<< orphan*/  s_81 ; 
 int /*<<< orphan*/  s_82 ; 
 int /*<<< orphan*/  s_83 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5c(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* do, line 478 */
        z->ket = z->c; /* [, line 479 */
        if (z->c - 9 <= z->lb || z->p[z->c - 1] != 181) goto lab0; /* substring, line 479 */
        if (!(find_among_b(z, a_45, 1))) goto lab0;
        z->bra = z->c; /* ], line 479 */
        {   int ret = slice_del(z); /* delete, line 480 */
            if (ret < 0) return ret;
        }
        z->B[0] = 0; /* unset test1, line 480 */
    lab0:
        z->c = z->l - m1;
    }
    z->ket = z->c; /* [, line 483 */
    if (!(eq_s_b(z, 6, s_80))) return 0; /* literal, line 483 */
    z->bra = z->c; /* ], line 483 */
    {   int ret = slice_del(z); /* delete, line 484 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 485 */
    {   int m2 = z->l - z->c; (void)m2; /* or, line 486 */
        z->ket = z->c; /* [, line 486 */
        if (in_grouping_b_U(z, g_v2, 945, 969, 0)) goto lab2; /* grouping v2, line 486 */
        z->bra = z->c; /* ], line 486 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 486 */
        if (z->S[0] == 0) return -1; /* -> s, line 486 */
        {   int ret = slice_from_s(z, 4, s_81); /* <-, line 486 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 486 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab1;
    lab2:
        z->c = z->l - m2;
        z->ket = z->c; /* [, line 487 */
        if (!(find_among_b(z, a_46, 31))) goto lab3; /* substring, line 487 */
        z->bra = z->c; /* ], line 487 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 491 */
        if (z->S[0] == 0) return -1; /* -> s, line 491 */
        {   int ret = slice_from_s(z, 4, s_82); /* <-, line 491 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 491 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab1;
    lab3:
        z->c = z->l - m2;
        z->ket = z->c; /* [, line 493 */
    }
lab1:
    if (!(find_among_b(z, a_47, 25))) return 0; /* substring, line 493 */
    z->bra = z->c; /* ], line 493 */
    if (z->c > z->lb) return 0; /* atlimit, line 493 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 497 */
    if (z->S[0] == 0) return -1; /* -> s, line 497 */
    {   int ret = slice_from_s(z, 4, s_83); /* <-, line 497 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 497 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}