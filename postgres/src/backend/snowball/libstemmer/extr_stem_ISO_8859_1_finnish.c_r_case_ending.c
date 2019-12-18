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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; char* p; int l; int* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_6 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_C ; 
 int /*<<< orphan*/  g_V1 ; 
 int /*<<< orphan*/  in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_LONG (struct SN_env*) ; 
 int /*<<< orphan*/  s_2 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_case_ending(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 97 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 97 */
        among_var = find_among_b(z, a_6, 30); /* substring, line 97 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 97 */
        z->lb = mlimit1;
    }
    switch (among_var) { /* among, line 98 */
        case 1:
            if (z->c <= z->lb || z->p[z->c - 1] != 'a') return 0; /* literal, line 99 */
            z->c--;
            break;
        case 2:
            if (z->c <= z->lb || z->p[z->c - 1] != 'e') return 0; /* literal, line 100 */
            z->c--;
            break;
        case 3:
            if (z->c <= z->lb || z->p[z->c - 1] != 'i') return 0; /* literal, line 101 */
            z->c--;
            break;
        case 4:
            if (z->c <= z->lb || z->p[z->c - 1] != 'o') return 0; /* literal, line 102 */
            z->c--;
            break;
        case 5:
            if (z->c <= z->lb || z->p[z->c - 1] != 0xE4) return 0; /* literal, line 103 */
            z->c--;
            break;
        case 6:
            if (z->c <= z->lb || z->p[z->c - 1] != 0xF6) return 0; /* literal, line 104 */
            z->c--;
            break;
        case 7:
            {   int m2 = z->l - z->c; (void)m2; /* try, line 112 */
                {   int m3 = z->l - z->c; (void)m3; /* and, line 114 */
                    {   int m4 = z->l - z->c; (void)m4; /* or, line 113 */
                        {   int ret = r_LONG(z); /* call LONG, line 112 */
                            if (ret == 0) goto lab2;
                            if (ret < 0) return ret;
                        }
                        goto lab1;
                    lab2:
                        z->c = z->l - m4;
                        if (!(eq_s_b(z, 2, s_2))) { z->c = z->l - m2; goto lab0; } /* literal, line 113 */
                    }
                lab1:
                    z->c = z->l - m3;
                    if (z->c <= z->lb) { z->c = z->l - m2; goto lab0; }
                    z->c--; /* next, line 114 */
                }
                z->bra = z->c; /* ], line 114 */
            lab0:
                ;
            }
            break;
        case 8:
            if (in_grouping_b(z, g_V1, 97, 246, 0)) return 0; /* grouping V1, line 120 */
            if (in_grouping_b(z, g_C, 98, 122, 0)) return 0; /* grouping C, line 120 */
            break;
    }
    {   int ret = slice_del(z); /* delete, line 139 */
        if (ret < 0) return ret;
    }
    z->B[0] = 1; /* set ending_removed, line 140 */
    return 1;
}