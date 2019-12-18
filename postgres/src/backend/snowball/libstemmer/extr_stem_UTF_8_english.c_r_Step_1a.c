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
struct SN_env {int l; int c; int ket; int lb; int* p; size_t bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  a_2 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 int out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int skip_utf8 (int*,size_t,size_t,int,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_1a(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m1 = z->l - z->c; (void)m1; /* try, line 59 */
        z->ket = z->c; /* [, line 60 */
        if (z->c <= z->lb || (z->p[z->c - 1] != 39 && z->p[z->c - 1] != 115)) { z->c = z->l - m1; goto lab0; } /* substring, line 60 */
        if (!(find_among_b(z, a_1, 3))) { z->c = z->l - m1; goto lab0; }
        z->bra = z->c; /* ], line 60 */
        {   int ret = slice_del(z); /* delete, line 62 */
            if (ret < 0) return ret;
        }
    lab0:
        ;
    }
    z->ket = z->c; /* [, line 65 */
    if (z->c <= z->lb || (z->p[z->c - 1] != 100 && z->p[z->c - 1] != 115)) return 0; /* substring, line 65 */
    among_var = find_among_b(z, a_2, 6);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 65 */
    switch (among_var) { /* among, line 65 */
        case 1:
            {   int ret = slice_from_s(z, 2, s_2); /* <-, line 66 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int m2 = z->l - z->c; (void)m2; /* or, line 68 */
                {   int ret = skip_utf8(z->p, z->c, z->lb, z->l, - 2); /* hop, line 68 */
                    if (ret < 0) goto lab2;
                    z->c = ret;
                }
                {   int ret = slice_from_s(z, 1, s_3); /* <-, line 68 */
                    if (ret < 0) return ret;
                }
                goto lab1;
            lab2:
                z->c = z->l - m2;
                {   int ret = slice_from_s(z, 2, s_4); /* <-, line 68 */
                    if (ret < 0) return ret;
                }
            }
        lab1:
            break;
        case 3:
            {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
                if (ret < 0) return 0;
                z->c = ret; /* next, line 69 */
            }
            {    /* gopast */ /* grouping v, line 69 */
                int ret = out_grouping_b_U(z, g_v, 97, 121, 1);
                if (ret < 0) return 0;
                z->c -= ret;
            }
            {   int ret = slice_del(z); /* delete, line 69 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}