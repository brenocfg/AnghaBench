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
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  a_5 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int r_RV (struct SN_env*) ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 77 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((823330 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 77 */
    among_var = find_among_b(z, a_5, 45);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 77 */
    switch (among_var) { /* among, line 77 */
        case 1:
            {   int ret = r_R2(z); /* call R2, line 93 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 93 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 98 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_4); /* <-, line 98 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = r_R2(z); /* call R2, line 102 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_5); /* <-, line 102 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = r_R2(z); /* call R2, line 106 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 4, s_6); /* <-, line 106 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R1(z); /* call R1, line 110 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 110 */
                if (ret < 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* try, line 111 */
                z->ket = z->c; /* [, line 112 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4718616 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m1; goto lab0; } /* substring, line 112 */
                among_var = find_among_b(z, a_2, 4);
                if (!(among_var)) { z->c = z->l - m1; goto lab0; }
                z->bra = z->c; /* ], line 112 */
                {   int ret = r_R2(z); /* call R2, line 112 */
                    if (ret == 0) { z->c = z->l - m1; goto lab0; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 112 */
                    if (ret < 0) return ret;
                }
                switch (among_var) { /* among, line 112 */
                    case 1:
                        z->ket = z->c; /* [, line 113 */
                        if (!(eq_s_b(z, 2, s_7))) { z->c = z->l - m1; goto lab0; } /* literal, line 113 */
                        z->bra = z->c; /* ], line 113 */
                        {   int ret = r_R2(z); /* call R2, line 113 */
                            if (ret == 0) { z->c = z->l - m1; goto lab0; }
                            if (ret < 0) return ret;
                        }
                        {   int ret = slice_del(z); /* delete, line 113 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
            lab0:
                ;
            }
            break;
        case 6:
            {   int ret = r_R2(z); /* call R2, line 122 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 122 */
                if (ret < 0) return ret;
            }
            {   int m2 = z->l - z->c; (void)m2; /* try, line 123 */
                z->ket = z->c; /* [, line 124 */
                if (z->c - 3 <= z->lb || (z->p[z->c - 1] != 101 && z->p[z->c - 1] != 108)) { z->c = z->l - m2; goto lab1; } /* substring, line 124 */
                if (!(find_among_b(z, a_3, 3))) { z->c = z->l - m2; goto lab1; }
                z->bra = z->c; /* ], line 124 */
                {   int ret = r_R2(z); /* call R2, line 127 */
                    if (ret == 0) { z->c = z->l - m2; goto lab1; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 127 */
                    if (ret < 0) return ret;
                }
            lab1:
                ;
            }
            break;
        case 7:
            {   int ret = r_R2(z); /* call R2, line 134 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 134 */
                if (ret < 0) return ret;
            }
            {   int m3 = z->l - z->c; (void)m3; /* try, line 135 */
                z->ket = z->c; /* [, line 136 */
                if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4198408 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->c = z->l - m3; goto lab2; } /* substring, line 136 */
                if (!(find_among_b(z, a_4, 3))) { z->c = z->l - m3; goto lab2; }
                z->bra = z->c; /* ], line 136 */
                {   int ret = r_R2(z); /* call R2, line 139 */
                    if (ret == 0) { z->c = z->l - m3; goto lab2; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 139 */
                    if (ret < 0) return ret;
                }
            lab2:
                ;
            }
            break;
        case 8:
            {   int ret = r_R2(z); /* call R2, line 146 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 146 */
                if (ret < 0) return ret;
            }
            {   int m4 = z->l - z->c; (void)m4; /* try, line 147 */
                z->ket = z->c; /* [, line 148 */
                if (!(eq_s_b(z, 2, s_8))) { z->c = z->l - m4; goto lab3; } /* literal, line 148 */
                z->bra = z->c; /* ], line 148 */
                {   int ret = r_R2(z); /* call R2, line 148 */
                    if (ret == 0) { z->c = z->l - m4; goto lab3; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 148 */
                    if (ret < 0) return ret;
                }
            lab3:
                ;
            }
            break;
        case 9:
            {   int ret = r_RV(z); /* call RV, line 153 */
                if (ret <= 0) return ret;
            }
            if (z->c <= z->lb || z->p[z->c - 1] != 'e') return 0; /* literal, line 153 */
            z->c--;
            {   int ret = slice_from_s(z, 2, s_9); /* <-, line 154 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}