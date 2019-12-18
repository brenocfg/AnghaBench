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
struct SN_env {int ket; int c; int bra; int l; int* p; int /*<<< orphan*/  lb; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 int /*<<< orphan*/  in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int r_RV (struct SN_env*) ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_16 ; 
 int /*<<< orphan*/  s_17 ; 
 int /*<<< orphan*/  s_18 ; 
 int /*<<< orphan*/  s_19 ; 
 int /*<<< orphan*/  s_20 ; 
 int /*<<< orphan*/  s_21 ; 
 int /*<<< orphan*/  s_22 ; 
 int /*<<< orphan*/  s_23 ; 
 int /*<<< orphan*/  s_24 ; 
 int /*<<< orphan*/  s_25 ; 
 int /*<<< orphan*/  s_26 ; 
 int /*<<< orphan*/  s_27 ; 
 int /*<<< orphan*/  s_28 ; 
 int /*<<< orphan*/  s_29 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 99 */
    among_var = find_among_b(z, a_4, 43); /* substring, line 99 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 99 */
    switch (among_var) { /* among, line 99 */
        case 1:
            {   int ret = r_R2(z); /* call R2, line 103 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 103 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 106 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 106 */
                if (ret < 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* try, line 107 */
                z->ket = z->c; /* [, line 107 */
                if (!(eq_s_b(z, 2, s_12))) { z->c = z->l - m1; goto lab0; } /* literal, line 107 */
                z->bra = z->c; /* ], line 107 */
                {   int m2 = z->l - z->c; (void)m2; /* or, line 107 */
                    {   int ret = r_R2(z); /* call R2, line 107 */
                        if (ret == 0) goto lab2;
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 107 */
                        if (ret < 0) return ret;
                    }
                    goto lab1;
                lab2:
                    z->c = z->l - m2;
                    {   int ret = slice_from_s(z, 3, s_13); /* <-, line 107 */
                        if (ret < 0) return ret;
                    }
                }
            lab1:
            lab0:
                ;
            }
            break;
        case 3:
            {   int ret = r_R2(z); /* call R2, line 111 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_14); /* <-, line 111 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = r_R2(z); /* call R2, line 114 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_15); /* <-, line 114 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R2(z); /* call R2, line 117 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_16); /* <-, line 117 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_RV(z); /* call RV, line 121 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 121 */
                if (ret < 0) return ret;
            }
            {   int m3 = z->l - z->c; (void)m3; /* try, line 122 */
                z->ket = z->c; /* [, line 123 */
                among_var = find_among_b(z, a_2, 6); /* substring, line 123 */
                if (!(among_var)) { z->c = z->l - m3; goto lab3; }
                z->bra = z->c; /* ], line 123 */
                switch (among_var) { /* among, line 123 */
                    case 1:
                        {   int ret = r_R2(z); /* call R2, line 124 */
                            if (ret == 0) { z->c = z->l - m3; goto lab3; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 124 */
                            if (ret < 0) return ret;
                        }
                        z->ket = z->c; /* [, line 124 */
                        if (!(eq_s_b(z, 2, s_17))) { z->c = z->l - m3; goto lab3; } /* literal, line 124 */
                        z->bra = z->c; /* ], line 124 */
                        {   int ret = r_R2(z); /* call R2, line 124 */
                            if (ret == 0) { z->c = z->l - m3; goto lab3; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 124 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 2:
                        {   int m4 = z->l - z->c; (void)m4; /* or, line 125 */
                            {   int ret = r_R2(z); /* call R2, line 125 */
                                if (ret == 0) goto lab5;
                                if (ret < 0) return ret;
                            }
                            {   int ret = slice_del(z); /* delete, line 125 */
                                if (ret < 0) return ret;
                            }
                            goto lab4;
                        lab5:
                            z->c = z->l - m4;
                            {   int ret = r_R1(z); /* call R1, line 125 */
                                if (ret == 0) { z->c = z->l - m3; goto lab3; }
                                if (ret < 0) return ret;
                            }
                            {   int ret = slice_from_s(z, 3, s_18); /* <-, line 125 */
                                if (ret < 0) return ret;
                            }
                        }
                    lab4:
                        break;
                    case 3:
                        {   int ret = r_R2(z); /* call R2, line 127 */
                            if (ret == 0) { z->c = z->l - m3; goto lab3; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 127 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 4:
                        {   int ret = r_RV(z); /* call RV, line 129 */
                            if (ret == 0) { z->c = z->l - m3; goto lab3; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_from_s(z, 1, s_19); /* <-, line 129 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
            lab3:
                ;
            }
            break;
        case 7:
            {   int ret = r_R2(z); /* call R2, line 136 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 136 */
                if (ret < 0) return ret;
            }
            {   int m5 = z->l - z->c; (void)m5; /* try, line 137 */
                z->ket = z->c; /* [, line 138 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4198408 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m5; goto lab6; } /* substring, line 138 */
                among_var = find_among_b(z, a_3, 3);
                if (!(among_var)) { z->c = z->l - m5; goto lab6; }
                z->bra = z->c; /* ], line 138 */
                switch (among_var) { /* among, line 138 */
                    case 1:
                        {   int m6 = z->l - z->c; (void)m6; /* or, line 139 */
                            {   int ret = r_R2(z); /* call R2, line 139 */
                                if (ret == 0) goto lab8;
                                if (ret < 0) return ret;
                            }
                            {   int ret = slice_del(z); /* delete, line 139 */
                                if (ret < 0) return ret;
                            }
                            goto lab7;
                        lab8:
                            z->c = z->l - m6;
                            {   int ret = slice_from_s(z, 3, s_20); /* <-, line 139 */
                                if (ret < 0) return ret;
                            }
                        }
                    lab7:
                        break;
                    case 2:
                        {   int m7 = z->l - z->c; (void)m7; /* or, line 140 */
                            {   int ret = r_R2(z); /* call R2, line 140 */
                                if (ret == 0) goto lab10;
                                if (ret < 0) return ret;
                            }
                            {   int ret = slice_del(z); /* delete, line 140 */
                                if (ret < 0) return ret;
                            }
                            goto lab9;
                        lab10:
                            z->c = z->l - m7;
                            {   int ret = slice_from_s(z, 3, s_21); /* <-, line 140 */
                                if (ret < 0) return ret;
                            }
                        }
                    lab9:
                        break;
                    case 3:
                        {   int ret = r_R2(z); /* call R2, line 141 */
                            if (ret == 0) { z->c = z->l - m5; goto lab6; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 141 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
            lab6:
                ;
            }
            break;
        case 8:
            {   int ret = r_R2(z); /* call R2, line 148 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 148 */
                if (ret < 0) return ret;
            }
            {   int m8 = z->l - z->c; (void)m8; /* try, line 149 */
                z->ket = z->c; /* [, line 149 */
                if (!(eq_s_b(z, 2, s_22))) { z->c = z->l - m8; goto lab11; } /* literal, line 149 */
                z->bra = z->c; /* ], line 149 */
                {   int ret = r_R2(z); /* call R2, line 149 */
                    if (ret == 0) { z->c = z->l - m8; goto lab11; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 149 */
                    if (ret < 0) return ret;
                }
                z->ket = z->c; /* [, line 149 */
                if (!(eq_s_b(z, 2, s_23))) { z->c = z->l - m8; goto lab11; } /* literal, line 149 */
                z->bra = z->c; /* ], line 149 */
                {   int m9 = z->l - z->c; (void)m9; /* or, line 149 */
                    {   int ret = r_R2(z); /* call R2, line 149 */
                        if (ret == 0) goto lab13;
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 149 */
                        if (ret < 0) return ret;
                    }
                    goto lab12;
                lab13:
                    z->c = z->l - m9;
                    {   int ret = slice_from_s(z, 3, s_24); /* <-, line 149 */
                        if (ret < 0) return ret;
                    }
                }
            lab12:
            lab11:
                ;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 3, s_25); /* <-, line 151 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = r_R1(z); /* call R1, line 152 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 2, s_26); /* <-, line 152 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int m10 = z->l - z->c; (void)m10; /* or, line 154 */
                {   int ret = r_R2(z); /* call R2, line 154 */
                    if (ret == 0) goto lab15;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 154 */
                    if (ret < 0) return ret;
                }
                goto lab14;
            lab15:
                z->c = z->l - m10;
                {   int ret = r_R1(z); /* call R1, line 154 */
                    if (ret <= 0) return ret;
                }
                {   int ret = slice_from_s(z, 3, s_27); /* <-, line 154 */
                    if (ret < 0) return ret;
                }
            }
        lab14:
            break;
        case 12:
            {   int ret = r_R1(z); /* call R1, line 157 */
                if (ret <= 0) return ret;
            }
            if (out_grouping_b(z, g_v, 97, 251, 0)) return 0; /* non v, line 157 */
            {   int ret = slice_del(z); /* delete, line 157 */
                if (ret < 0) return ret;
            }
            break;
        case 13:
            {   int ret = r_RV(z); /* call RV, line 162 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_28); /* <-, line 162 */
                if (ret < 0) return ret;
            }
            return 0; /* fail, line 162 */
            break;
        case 14:
            {   int ret = r_RV(z); /* call RV, line 163 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_29); /* <-, line 163 */
                if (ret < 0) return ret;
            }
            return 0; /* fail, line 163 */
            break;
        case 15:
            {   int m_test11 = z->l - z->c; /* test, line 165 */
                if (in_grouping_b(z, g_v, 97, 251, 0)) return 0; /* grouping v, line 165 */
                {   int ret = r_RV(z); /* call RV, line 165 */
                    if (ret <= 0) return ret;
                }
                z->c = z->l - m_test11;
            }
            {   int ret = slice_del(z); /* delete, line 165 */
                if (ret < 0) return ret;
            }
            return 0; /* fail, line 165 */
            break;
    }
    return 1;
}