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
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  a_5 ; 
 int /*<<< orphan*/  a_6 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int r_RV (struct SN_env*) ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_16 ; 
 int /*<<< orphan*/  s_17 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 104 */
    among_var = find_among_b(z, a_6, 51); /* substring, line 104 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 104 */
    switch (among_var) { /* among, line 104 */
        case 1:
            {   int ret = r_R2(z); /* call R2, line 111 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 111 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 113 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 113 */
                if (ret < 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* try, line 114 */
                z->ket = z->c; /* [, line 114 */
                if (!(eq_s_b(z, 2, s_11))) { z->c = z->l - m1; goto lab0; } /* literal, line 114 */
                z->bra = z->c; /* ], line 114 */
                {   int ret = r_R2(z); /* call R2, line 114 */
                    if (ret == 0) { z->c = z->l - m1; goto lab0; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 114 */
                    if (ret < 0) return ret;
                }
            lab0:
                ;
            }
            break;
        case 3:
            {   int ret = r_R2(z); /* call R2, line 117 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_12); /* <-, line 117 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = r_R2(z); /* call R2, line 119 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_13); /* <-, line 119 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R2(z); /* call R2, line 121 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 4, s_14); /* <-, line 121 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_RV(z); /* call RV, line 123 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 123 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = r_R1(z); /* call R1, line 125 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 125 */
                if (ret < 0) return ret;
            }
            {   int m2 = z->l - z->c; (void)m2; /* try, line 126 */
                z->ket = z->c; /* [, line 127 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4722696 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m2; goto lab1; } /* substring, line 127 */
                among_var = find_among_b(z, a_4, 4);
                if (!(among_var)) { z->c = z->l - m2; goto lab1; }
                z->bra = z->c; /* ], line 127 */
                {   int ret = r_R2(z); /* call R2, line 127 */
                    if (ret == 0) { z->c = z->l - m2; goto lab1; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 127 */
                    if (ret < 0) return ret;
                }
                switch (among_var) { /* among, line 127 */
                    case 1:
                        z->ket = z->c; /* [, line 128 */
                        if (!(eq_s_b(z, 2, s_15))) { z->c = z->l - m2; goto lab1; } /* literal, line 128 */
                        z->bra = z->c; /* ], line 128 */
                        {   int ret = r_R2(z); /* call R2, line 128 */
                            if (ret == 0) { z->c = z->l - m2; goto lab1; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 128 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
            lab1:
                ;
            }
            break;
        case 8:
            {   int ret = r_R2(z); /* call R2, line 134 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 134 */
                if (ret < 0) return ret;
            }
            {   int m3 = z->l - z->c; (void)m3; /* try, line 135 */
                z->ket = z->c; /* [, line 136 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4198408 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m3; goto lab2; } /* substring, line 136 */
                if (!(find_among_b(z, a_5, 3))) { z->c = z->l - m3; goto lab2; }
                z->bra = z->c; /* ], line 136 */
                {   int ret = r_R2(z); /* call R2, line 137 */
                    if (ret == 0) { z->c = z->l - m3; goto lab2; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 137 */
                    if (ret < 0) return ret;
                }
            lab2:
                ;
            }
            break;
        case 9:
            {   int ret = r_R2(z); /* call R2, line 142 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 142 */
                if (ret < 0) return ret;
            }
            {   int m4 = z->l - z->c; (void)m4; /* try, line 143 */
                z->ket = z->c; /* [, line 143 */
                if (!(eq_s_b(z, 2, s_16))) { z->c = z->l - m4; goto lab3; } /* literal, line 143 */
                z->bra = z->c; /* ], line 143 */
                {   int ret = r_R2(z); /* call R2, line 143 */
                    if (ret == 0) { z->c = z->l - m4; goto lab3; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 143 */
                    if (ret < 0) return ret;
                }
                z->ket = z->c; /* [, line 143 */
                if (!(eq_s_b(z, 2, s_17))) { z->c = z->l - m4; goto lab3; } /* literal, line 143 */
                z->bra = z->c; /* ], line 143 */
                {   int ret = r_R2(z); /* call R2, line 143 */
                    if (ret == 0) { z->c = z->l - m4; goto lab3; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 143 */
                    if (ret < 0) return ret;
                }
            lab3:
                ;
            }
            break;
    }
    return 1;
}