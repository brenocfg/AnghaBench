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
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_s_ending ; 
 int /*<<< orphan*/  g_st_ending ; 
 int /*<<< orphan*/  in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int*,size_t,int,int,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m1 = z->l - z->c; (void)m1; /* do, line 79 */
        z->ket = z->c; /* [, line 80 */
        if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((811040 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab0; /* substring, line 80 */
        among_var = find_among_b(z, a_1, 7);
        if (!(among_var)) goto lab0;
        z->bra = z->c; /* ], line 80 */
        {   int ret = r_R1(z); /* call R1, line 80 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 80 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 82 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z); /* delete, line 85 */
                    if (ret < 0) return ret;
                }
                {   int m2 = z->l - z->c; (void)m2; /* try, line 86 */
                    z->ket = z->c; /* [, line 86 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 's') { z->c = z->l - m2; goto lab1; } /* literal, line 86 */
                    z->c--;
                    z->bra = z->c; /* ], line 86 */
                    if (!(eq_s_b(z, 3, s_8))) { z->c = z->l - m2; goto lab1; } /* literal, line 86 */
                    {   int ret = slice_del(z); /* delete, line 86 */
                        if (ret < 0) return ret;
                    }
                lab1:
                    ;
                }
                break;
            case 3:
                if (in_grouping_b_U(z, g_s_ending, 98, 116, 0)) goto lab0; /* grouping s_ending, line 89 */
                {   int ret = slice_del(z); /* delete, line 89 */
                    if (ret < 0) return ret;
                }
                break;
        }
    lab0:
        z->c = z->l - m1;
    }
    {   int m3 = z->l - z->c; (void)m3; /* do, line 93 */
        z->ket = z->c; /* [, line 94 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1327104 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab2; /* substring, line 94 */
        among_var = find_among_b(z, a_2, 4);
        if (!(among_var)) goto lab2;
        z->bra = z->c; /* ], line 94 */
        {   int ret = r_R1(z); /* call R1, line 94 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 94 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 96 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                if (in_grouping_b_U(z, g_st_ending, 98, 116, 0)) goto lab2; /* grouping st_ending, line 99 */
                {   int ret = skip_utf8(z->p, z->c, z->lb, z->l, - 3); /* hop, line 99 */
                    if (ret < 0) goto lab2;
                    z->c = ret;
                }
                {   int ret = slice_del(z); /* delete, line 99 */
                    if (ret < 0) return ret;
                }
                break;
        }
    lab2:
        z->c = z->l - m3;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 103 */
        z->ket = z->c; /* [, line 104 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1051024 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab3; /* substring, line 104 */
        among_var = find_among_b(z, a_4, 8);
        if (!(among_var)) goto lab3;
        z->bra = z->c; /* ], line 104 */
        {   int ret = r_R2(z); /* call R2, line 104 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 104 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 106 */
                    if (ret < 0) return ret;
                }
                {   int m5 = z->l - z->c; (void)m5; /* try, line 107 */
                    z->ket = z->c; /* [, line 107 */
                    if (!(eq_s_b(z, 2, s_9))) { z->c = z->l - m5; goto lab4; } /* literal, line 107 */
                    z->bra = z->c; /* ], line 107 */
                    {   int m6 = z->l - z->c; (void)m6; /* not, line 107 */
                        if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab5; /* literal, line 107 */
                        z->c--;
                        { z->c = z->l - m5; goto lab4; }
                    lab5:
                        z->c = z->l - m6;
                    }
                    {   int ret = r_R2(z); /* call R2, line 107 */
                        if (ret == 0) { z->c = z->l - m5; goto lab4; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 107 */
                        if (ret < 0) return ret;
                    }
                lab4:
                    ;
                }
                break;
            case 2:
                {   int m7 = z->l - z->c; (void)m7; /* not, line 110 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab6; /* literal, line 110 */
                    z->c--;
                    goto lab3;
                lab6:
                    z->c = z->l - m7;
                }
                {   int ret = slice_del(z); /* delete, line 110 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_del(z); /* delete, line 113 */
                    if (ret < 0) return ret;
                }
                {   int m8 = z->l - z->c; (void)m8; /* try, line 114 */
                    z->ket = z->c; /* [, line 115 */
                    {   int m9 = z->l - z->c; (void)m9; /* or, line 115 */
                        if (!(eq_s_b(z, 2, s_10))) goto lab9; /* literal, line 115 */
                        goto lab8;
                    lab9:
                        z->c = z->l - m9;
                        if (!(eq_s_b(z, 2, s_11))) { z->c = z->l - m8; goto lab7; } /* literal, line 115 */
                    }
                lab8:
                    z->bra = z->c; /* ], line 115 */
                    {   int ret = r_R1(z); /* call R1, line 115 */
                        if (ret == 0) { z->c = z->l - m8; goto lab7; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 115 */
                        if (ret < 0) return ret;
                    }
                lab7:
                    ;
                }
                break;
            case 4:
                {   int ret = slice_del(z); /* delete, line 119 */
                    if (ret < 0) return ret;
                }
                {   int m10 = z->l - z->c; (void)m10; /* try, line 120 */
                    z->ket = z->c; /* [, line 121 */
                    if (z->c - 1 <= z->lb || (z->p[z->c - 1] != 103 && z->p[z->c - 1] != 104)) { z->c = z->l - m10; goto lab10; } /* substring, line 121 */
                    if (!(find_among_b(z, a_3, 2))) { z->c = z->l - m10; goto lab10; }
                    z->bra = z->c; /* ], line 121 */
                    {   int ret = r_R2(z); /* call R2, line 121 */
                        if (ret == 0) { z->c = z->l - m10; goto lab10; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 123 */
                        if (ret < 0) return ret;
                    }
                lab10:
                    ;
                }
                break;
        }
    lab3:
        z->c = z->l - m4;
    }
    return 1;
}