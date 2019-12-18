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
struct SN_env {int c; int bra; int ket; int l; unsigned char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_prelude(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c_test1 = z->c; /* test, line 35 */
        while(1) { /* repeat, line 35 */
            int c2 = z->c;
            z->bra = z->c; /* [, line 36 */
            among_var = find_among(z, a_0, 7); /* substring, line 36 */
            if (!(among_var)) goto lab0;
            z->ket = z->c; /* ], line 36 */
            switch (among_var) { /* among, line 36 */
                case 1:
                    {   int ret = slice_from_s(z, 1, s_0); /* <-, line 37 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 2:
                    {   int ret = slice_from_s(z, 1, s_1); /* <-, line 38 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 3:
                    {   int ret = slice_from_s(z, 1, s_2); /* <-, line 39 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 4:
                    {   int ret = slice_from_s(z, 1, s_3); /* <-, line 40 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 5:
                    {   int ret = slice_from_s(z, 1, s_4); /* <-, line 41 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 6:
                    {   int ret = slice_from_s(z, 2, s_5); /* <-, line 42 */
                        if (ret < 0) return ret;
                    }
                    break;
                case 7:
                    if (z->c >= z->l) goto lab0;
                    z->c++; /* next, line 43 */
                    break;
            }
            continue;
        lab0:
            z->c = c2;
            break;
        }
        z->c = c_test1;
    }
    while(1) { /* repeat, line 46 */
        int c3 = z->c;
        while(1) { /* goto, line 46 */
            int c4 = z->c;
            if (in_grouping(z, g_v, 97, 249, 0)) goto lab2; /* grouping v, line 47 */
            z->bra = z->c; /* [, line 47 */
            {   int c5 = z->c; /* or, line 47 */
                if (z->c == z->l || z->p[z->c] != 'u') goto lab4; /* literal, line 47 */
                z->c++;
                z->ket = z->c; /* ], line 47 */
                if (in_grouping(z, g_v, 97, 249, 0)) goto lab4; /* grouping v, line 47 */
                {   int ret = slice_from_s(z, 1, s_6); /* <-, line 47 */
                    if (ret < 0) return ret;
                }
                goto lab3;
            lab4:
                z->c = c5;
                if (z->c == z->l || z->p[z->c] != 'i') goto lab2; /* literal, line 48 */
                z->c++;
                z->ket = z->c; /* ], line 48 */
                if (in_grouping(z, g_v, 97, 249, 0)) goto lab2; /* grouping v, line 48 */
                {   int ret = slice_from_s(z, 1, s_7); /* <-, line 48 */
                    if (ret < 0) return ret;
                }
            }
        lab3:
            z->c = c4;
            break;
        lab2:
            z->c = c4;
            if (z->c >= z->l) goto lab1;
            z->c++; /* goto, line 46 */
        }
        continue;
    lab1:
        z->c = c3;
        break;
    }
    return 1;
}