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
struct SN_env {int c; int bra; int l; unsigned char* p; size_t ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int skip_utf8 (unsigned char*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_prelude(struct SN_env * z) { /* forwardmode */
    while(1) { /* repeat, line 38 */
        int c1 = z->c;
        while(1) { /* goto, line 38 */
            int c2 = z->c;
            {   int c3 = z->c; /* or, line 44 */
                if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab3; /* grouping v, line 40 */
                z->bra = z->c; /* [, line 40 */
                {   int c4 = z->c; /* or, line 40 */
                    if (z->c == z->l || z->p[z->c] != 'u') goto lab5; /* literal, line 40 */
                    z->c++;
                    z->ket = z->c; /* ], line 40 */
                    if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab5; /* grouping v, line 40 */
                    {   int ret = slice_from_s(z, 1, s_0); /* <-, line 40 */
                        if (ret < 0) return ret;
                    }
                    goto lab4;
                lab5:
                    z->c = c4;
                    if (z->c == z->l || z->p[z->c] != 'i') goto lab6; /* literal, line 41 */
                    z->c++;
                    z->ket = z->c; /* ], line 41 */
                    if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab6; /* grouping v, line 41 */
                    {   int ret = slice_from_s(z, 1, s_1); /* <-, line 41 */
                        if (ret < 0) return ret;
                    }
                    goto lab4;
                lab6:
                    z->c = c4;
                    if (z->c == z->l || z->p[z->c] != 'y') goto lab3; /* literal, line 42 */
                    z->c++;
                    z->ket = z->c; /* ], line 42 */
                    {   int ret = slice_from_s(z, 1, s_2); /* <-, line 42 */
                        if (ret < 0) return ret;
                    }
                }
            lab4:
                goto lab2;
            lab3:
                z->c = c3;
                z->bra = z->c; /* [, line 45 */
                if (!(eq_s(z, 2, s_3))) goto lab7; /* literal, line 45 */
                z->ket = z->c; /* ], line 45 */
                {   int ret = slice_from_s(z, 2, s_4); /* <-, line 45 */
                    if (ret < 0) return ret;
                }
                goto lab2;
            lab7:
                z->c = c3;
                z->bra = z->c; /* [, line 47 */
                if (!(eq_s(z, 2, s_5))) goto lab8; /* literal, line 47 */
                z->ket = z->c; /* ], line 47 */
                {   int ret = slice_from_s(z, 2, s_6); /* <-, line 47 */
                    if (ret < 0) return ret;
                }
                goto lab2;
            lab8:
                z->c = c3;
                z->bra = z->c; /* [, line 49 */
                if (z->c == z->l || z->p[z->c] != 'y') goto lab9; /* literal, line 49 */
                z->c++;
                z->ket = z->c; /* ], line 49 */
                if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab9; /* grouping v, line 49 */
                {   int ret = slice_from_s(z, 1, s_7); /* <-, line 49 */
                    if (ret < 0) return ret;
                }
                goto lab2;
            lab9:
                z->c = c3;
                if (z->c == z->l || z->p[z->c] != 'q') goto lab1; /* literal, line 51 */
                z->c++;
                z->bra = z->c; /* [, line 51 */
                if (z->c == z->l || z->p[z->c] != 'u') goto lab1; /* literal, line 51 */
                z->c++;
                z->ket = z->c; /* ], line 51 */
                {   int ret = slice_from_s(z, 1, s_8); /* <-, line 51 */
                    if (ret < 0) return ret;
                }
            }
        lab2:
            z->c = c2;
            break;
        lab1:
            z->c = c2;
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab0;
                z->c = ret; /* goto, line 38 */
            }
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}