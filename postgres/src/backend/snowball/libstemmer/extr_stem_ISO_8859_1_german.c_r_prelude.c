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
struct SN_env {int c; int bra; int l; int* p; size_t ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_prelude(struct SN_env * z) { /* forwardmode */
    {   int c_test1 = z->c; /* test, line 35 */
        while(1) { /* repeat, line 35 */
            int c2 = z->c;
            {   int c3 = z->c; /* or, line 38 */
                z->bra = z->c; /* [, line 37 */
                if (z->c == z->l || z->p[z->c] != 0xDF) goto lab2; /* literal, line 37 */
                z->c++;
                z->ket = z->c; /* ], line 37 */
                {   int ret = slice_from_s(z, 2, s_0); /* <-, line 37 */
                    if (ret < 0) return ret;
                }
                goto lab1;
            lab2:
                z->c = c3;
                if (z->c >= z->l) goto lab0;
                z->c++; /* next, line 38 */
            }
        lab1:
            continue;
        lab0:
            z->c = c2;
            break;
        }
        z->c = c_test1;
    }
    while(1) { /* repeat, line 41 */
        int c4 = z->c;
        while(1) { /* goto, line 41 */
            int c5 = z->c;
            if (in_grouping(z, g_v, 97, 252, 0)) goto lab4; /* grouping v, line 42 */
            z->bra = z->c; /* [, line 42 */
            {   int c6 = z->c; /* or, line 42 */
                if (z->c == z->l || z->p[z->c] != 'u') goto lab6; /* literal, line 42 */
                z->c++;
                z->ket = z->c; /* ], line 42 */
                if (in_grouping(z, g_v, 97, 252, 0)) goto lab6; /* grouping v, line 42 */
                {   int ret = slice_from_s(z, 1, s_1); /* <-, line 42 */
                    if (ret < 0) return ret;
                }
                goto lab5;
            lab6:
                z->c = c6;
                if (z->c == z->l || z->p[z->c] != 'y') goto lab4; /* literal, line 43 */
                z->c++;
                z->ket = z->c; /* ], line 43 */
                if (in_grouping(z, g_v, 97, 252, 0)) goto lab4; /* grouping v, line 43 */
                {   int ret = slice_from_s(z, 1, s_2); /* <-, line 43 */
                    if (ret < 0) return ret;
                }
            }
        lab5:
            z->c = c5;
            break;
        lab4:
            z->c = c5;
            if (z->c >= z->l) goto lab3;
            z->c++; /* goto, line 41 */
        }
        continue;
    lab3:
        z->c = c4;
        break;
    }
    return 1;
}