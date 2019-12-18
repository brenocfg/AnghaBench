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
struct SN_env {int l; int c; int ket; int lb; char* p; int bra; int* I; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_7 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_keep_with_s ; 
 scalar_t__ out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R2 (struct SN_env*) ; 
 int /*<<< orphan*/  s_30 ; 
 int /*<<< orphan*/  s_31 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_residual_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m1 = z->l - z->c; (void)m1; /* try, line 206 */
        z->ket = z->c; /* [, line 206 */
        if (z->c <= z->lb || z->p[z->c - 1] != 's') { z->c = z->l - m1; goto lab0; } /* literal, line 206 */
        z->c--;
        z->bra = z->c; /* ], line 206 */
        {   int m_test2 = z->l - z->c; /* test, line 206 */
            {   int m3 = z->l - z->c; (void)m3; /* or, line 206 */
                if (!(eq_s_b(z, 2, s_30))) goto lab2; /* literal, line 206 */
                goto lab1;
            lab2:
                z->c = z->l - m3;
                if (out_grouping_b(z, g_keep_with_s, 97, 232, 0)) { z->c = z->l - m1; goto lab0; } /* non keep_with_s, line 206 */
            }
        lab1:
            z->c = z->l - m_test2;
        }
        {   int ret = slice_del(z); /* delete, line 206 */
            if (ret < 0) return ret;
        }
    lab0:
        ;
    }

    {   int mlimit4; /* setlimit, line 207 */
        if (z->c < z->I[0]) return 0;
        mlimit4 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 208 */
        if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((278560 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->lb = mlimit4; return 0; } /* substring, line 208 */
        among_var = find_among_b(z, a_7, 6);
        if (!(among_var)) { z->lb = mlimit4; return 0; }
        z->bra = z->c; /* ], line 208 */
        switch (among_var) { /* among, line 208 */
            case 1:
                {   int ret = r_R2(z); /* call R2, line 209 */
                    if (ret == 0) { z->lb = mlimit4; return 0; }
                    if (ret < 0) return ret;
                }
                {   int m5 = z->l - z->c; (void)m5; /* or, line 209 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 's') goto lab4; /* literal, line 209 */
                    z->c--;
                    goto lab3;
                lab4:
                    z->c = z->l - m5;
                    if (z->c <= z->lb || z->p[z->c - 1] != 't') { z->lb = mlimit4; return 0; } /* literal, line 209 */
                    z->c--;
                }
            lab3:
                {   int ret = slice_del(z); /* delete, line 209 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 1, s_31); /* <-, line 211 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_del(z); /* delete, line 212 */
                    if (ret < 0) return ret;
                }
                break;
        }
        z->lb = mlimit4;
    }
    return 1;
}