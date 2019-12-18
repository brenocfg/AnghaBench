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
struct SN_env {int c; int bra; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
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
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_prelude(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c_test1 = z->c; /* test, line 42 */
        while(1) { /* repeat, line 42 */
            int c2 = z->c;
            z->bra = z->c; /* [, line 43 */
            if (z->c + 1 >= z->l || z->p[z->c + 1] >> 5 != 5 || !((340306450 >> (z->p[z->c + 1] & 0x1f)) & 1)) among_var = 6; else /* substring, line 43 */
            among_var = find_among(z, a_0, 11);
            if (!(among_var)) goto lab0;
            z->ket = z->c; /* ], line 43 */
            switch (among_var) { /* among, line 43 */
                case 1:
                    {   int ret = slice_from_s(z, 1, s_0); /* <-, line 45 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 2:
                    {   int ret = slice_from_s(z, 1, s_1); /* <-, line 47 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 3:
                    {   int ret = slice_from_s(z, 1, s_2); /* <-, line 49 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 4:
                    {   int ret = slice_from_s(z, 1, s_3); /* <-, line 51 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 5:
                    {   int ret = slice_from_s(z, 1, s_4); /* <-, line 53 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 6:
                    {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                        if (ret < 0) goto lab0;
                        z->c = ret; /* next, line 54 */
                    }
                    break;
            }
            continue;
        lab0:
            z->c = c2;
            break;
        }
        z->c = c_test1;
    }
    {   int c3 = z->c; /* try, line 57 */
        z->bra = z->c; /* [, line 57 */
        if (z->c == z->l || z->p[z->c] != 'y') { z->c = c3; goto lab1; } /* literal, line 57 */
        z->c++;
        z->ket = z->c; /* ], line 57 */
        {   int ret = slice_from_s(z, 1, s_5); /* <-, line 57 */
            if (ret < 0) return ret;
        }
    lab1:
        ;
    }
    while(1) { /* repeat, line 58 */
        int c4 = z->c;
        while(1) { /* goto, line 58 */
            int c5 = z->c;
            if (in_grouping_U(z, g_v, 97, 232, 0)) goto lab3; /* grouping v, line 59 */
            z->bra = z->c; /* [, line 59 */
            {   int c6 = z->c; /* or, line 59 */
                if (z->c == z->l || z->p[z->c] != 'i') goto lab5; /* literal, line 59 */
                z->c++;
                z->ket = z->c; /* ], line 59 */
                if (in_grouping_U(z, g_v, 97, 232, 0)) goto lab5; /* grouping v, line 59 */
                {   int ret = slice_from_s(z, 1, s_6); /* <-, line 59 */
                    if (ret < 0) return ret;
                }
                goto lab4;
            lab5:
                z->c = c6;
                if (z->c == z->l || z->p[z->c] != 'y') goto lab3; /* literal, line 60 */
                z->c++;
                z->ket = z->c; /* ], line 60 */
                {   int ret = slice_from_s(z, 1, s_7); /* <-, line 60 */
                    if (ret < 0) return ret;
                }
            }
        lab4:
            z->c = c5;
            break;
        lab3:
            z->c = c5;
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab2;
                z->c = ret; /* goto, line 58 */
            }
        }
        continue;
    lab2:
        z->c = c4;
        break;
    }
    return 1;
}