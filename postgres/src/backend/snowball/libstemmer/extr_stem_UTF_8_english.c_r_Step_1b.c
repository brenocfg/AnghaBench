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
struct SN_env {int ket; int c; int lb; int* p; int bra; int* I; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 int insert_s (struct SN_env*,int,int,int,int /*<<< orphan*/ ) ; 
 int out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_shortv (struct SN_env*) ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int skip_utf8 (int*,int,int,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_1b(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 75 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((33554576 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 75 */
    among_var = find_among_b(z, a_4, 6);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 75 */
    switch (among_var) { /* among, line 75 */
        case 1:
            {   int ret = r_R1(z); /* call R1, line 77 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 2, s_5); /* <-, line 77 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int m_test1 = z->l - z->c; /* test, line 80 */
                {    /* gopast */ /* grouping v, line 80 */
                    int ret = out_grouping_b_U(z, g_v, 97, 121, 1);
                    if (ret < 0) return 0;
                    z->c -= ret;
                }
                z->c = z->l - m_test1;
            }
            {   int ret = slice_del(z); /* delete, line 80 */
                if (ret < 0) return ret;
            }
            {   int m_test2 = z->l - z->c; /* test, line 81 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((68514004 >> (z->p[z->c - 1] & 0x1f)) & 1)) among_var = 3; else /* substring, line 81 */
                among_var = find_among_b(z, a_3, 13);
                if (!(among_var)) return 0;
                z->c = z->l - m_test2;
            }
            switch (among_var) { /* among, line 81 */
                case 1:
                    {   int ret;
                        {   int saved_c = z->c;
                            ret = insert_s(z, z->c, z->c, 1, s_6); /* <+, line 83 */
                            z->c = saved_c;
                        }
                        if (ret < 0) return ret;
                    }
                    break;
                case 2:
                    z->ket = z->c; /* [, line 86 */
                    {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
                        if (ret < 0) return 0;
                        z->c = ret; /* next, line 86 */
                    }
                    z->bra = z->c; /* ], line 86 */
                    {   int ret = slice_del(z); /* delete, line 86 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 3:
                    if (z->c != z->I[0]) return 0; /* atmark, line 87 */
                    {   int m_test3 = z->l - z->c; /* test, line 87 */
                        {   int ret = r_shortv(z); /* call shortv, line 87 */
                            if (ret <= 0) return ret;
                        }
                        z->c = z->l - m_test3;
                    }
                    {   int ret;
                        {   int saved_c = z->c;
                            ret = insert_s(z, z->c, z->c, 1, s_7); /* <+, line 87 */
                            z->c = saved_c;
                        }
                        if (ret < 0) return ret;
                    }
                    break;
            }
            break;
    }
    return 1;
}