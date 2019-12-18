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
struct SN_env {int* B; int lb; int c; int l; int ket; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_13 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_46 ; 
 int /*<<< orphan*/  s_47 ; 
 int /*<<< orphan*/  s_48 ; 
 int /*<<< orphan*/  s_49 ; 
 int /*<<< orphan*/  s_50 ; 
 int /*<<< orphan*/  s_51 ; 
 int /*<<< orphan*/  s_52 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_remove_plural_suffix(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset found_a_match, line 168 */
    z->lb = z->c; z->c = z->l; /* backwards, line 169 */

    {   int m1 = z->l - z->c; (void)m1; /* or, line 170 */
        z->ket = z->c; /* [, line 170 */
        if (!(eq_s_b(z, 18, s_46))) goto lab1; /* literal, line 170 */
        {   int m_test2 = z->l - z->c; /* test, line 170 */
            {   int m3 = z->l - z->c; (void)m3; /* not, line 170 */
                if (!(find_among_b(z, a_13, 6))) goto lab2; /* among, line 170 */
                goto lab1;
            lab2:
                z->c = z->l - m3;
            }
            z->c = z->l - m_test2;
        }
        z->bra = z->c; /* ], line 170 */
        {   int ret = slice_from_s(z, 3, s_47); /* <-, line 170 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 171 */
        if (!(eq_s_b(z, 15, s_48))) goto lab3; /* literal, line 171 */
        z->bra = z->c; /* ], line 171 */
        {   int ret = slice_from_s(z, 6, s_49); /* <-, line 171 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab3:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 172 */
        if (!(eq_s_b(z, 15, s_50))) goto lab4; /* literal, line 172 */
        z->bra = z->c; /* ], line 172 */
        {   int ret = slice_from_s(z, 6, s_51); /* <-, line 172 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab4:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 173 */
        if (!(eq_s_b(z, 9, s_52))) return 0; /* literal, line 173 */
        z->bra = z->c; /* ], line 173 */
        {   int ret = slice_del(z); /* delete, line 173 */
            if (ret < 0) return ret;
        }
    }
lab0:
    z->B[0] = 1; /* set found_a_match, line 174 */
    z->c = z->lb;
    return 1;
}