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
struct SN_env {int ket; int c; int lb; int* p; int bra; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  a_5 ; 
 int /*<<< orphan*/  a_6 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 87 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((835634 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 87 */
    among_var = find_among_b(z, a_6, 46);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 87 */
    switch (among_var) { /* among, line 87 */
        case 1:
            {   int ret = r_R2(z); /* call R2, line 99 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 99 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 105 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 105 */
                if (ret < 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* try, line 106 */
                z->ket = z->c; /* [, line 106 */
                if (!(eq_s_b(z, 2, s_10))) { z->c = z->l - m1; goto lab0; } /* literal, line 106 */
                z->bra = z->c; /* ], line 106 */
                {   int ret = r_R2(z); /* call R2, line 106 */
                    if (ret == 0) { z->c = z->l - m1; goto lab0; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 106 */
                    if (ret < 0) return ret;
                }
            lab0:
                ;
            }
            break;
        case 3:
            {   int ret = r_R2(z); /* call R2, line 111 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_11); /* <-, line 111 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = r_R2(z); /* call R2, line 115 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_12); /* <-, line 115 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R2(z); /* call R2, line 119 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 4, s_13); /* <-, line 119 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_R1(z); /* call R1, line 123 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 123 */
                if (ret < 0) return ret;
            }
            {   int m2 = z->l - z->c; (void)m2; /* try, line 124 */
                z->ket = z->c; /* [, line 125 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4718616 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m2; goto lab1; } /* substring, line 125 */
                among_var = find_among_b(z, a_3, 4);
                if (!(among_var)) { z->c = z->l - m2; goto lab1; }
                z->bra = z->c; /* ], line 125 */
                {   int ret = r_R2(z); /* call R2, line 125 */
                    if (ret == 0) { z->c = z->l - m2; goto lab1; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 125 */
                    if (ret < 0) return ret;
                }
                switch (among_var) { /* among, line 125 */
                    case 1:
                        z->ket = z->c; /* [, line 126 */
                        if (!(eq_s_b(z, 2, s_14))) { z->c = z->l - m2; goto lab1; } /* literal, line 126 */
                        z->bra = z->c; /* ], line 126 */
                        {   int ret = r_R2(z); /* call R2, line 126 */
                            if (ret == 0) { z->c = z->l - m2; goto lab1; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 126 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
            lab1:
                ;
            }
            break;
        case 7:
            {   int ret = r_R2(z); /* call R2, line 135 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 135 */
                if (ret < 0) return ret;
            }
            {   int m3 = z->l - z->c; (void)m3; /* try, line 136 */
                z->ket = z->c; /* [, line 137 */
                if (z->c - 3 <= z->lb || z->p[z->c - 1] != 101) { z->c = z->l - m3; goto lab2; } /* substring, line 137 */
                if (!(find_among_b(z, a_4, 3))) { z->c = z->l - m3; goto lab2; }
                z->bra = z->c; /* ], line 137 */
                {   int ret = r_R2(z); /* call R2, line 140 */
                    if (ret == 0) { z->c = z->l - m3; goto lab2; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 140 */
                    if (ret < 0) return ret;
                }
            lab2:
                ;
            }
            break;
        case 8:
            {   int ret = r_R2(z); /* call R2, line 147 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 147 */
                if (ret < 0) return ret;
            }
            {   int m4 = z->l - z->c; (void)m4; /* try, line 148 */
                z->ket = z->c; /* [, line 149 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4198408 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m4; goto lab3; } /* substring, line 149 */
                if (!(find_among_b(z, a_5, 3))) { z->c = z->l - m4; goto lab3; }
                z->bra = z->c; /* ], line 149 */
                {   int ret = r_R2(z); /* call R2, line 152 */
                    if (ret == 0) { z->c = z->l - m4; goto lab3; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 152 */
                    if (ret < 0) return ret;
                }
            lab3:
                ;
            }
            break;
        case 9:
            {   int ret = r_R2(z); /* call R2, line 159 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 159 */
                if (ret < 0) return ret;
            }
            {   int m5 = z->l - z->c; (void)m5; /* try, line 160 */
                z->ket = z->c; /* [, line 161 */
                if (!(eq_s_b(z, 2, s_15))) { z->c = z->l - m5; goto lab4; } /* literal, line 161 */
                z->bra = z->c; /* ], line 161 */
                {   int ret = r_R2(z); /* call R2, line 161 */
                    if (ret == 0) { z->c = z->l - m5; goto lab4; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 161 */
                    if (ret < 0) return ret;
                }
            lab4:
                ;
            }
            break;
    }
    return 1;
}