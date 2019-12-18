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
struct SN_env {int bra; int c; int l; int* p; int ket; int* I; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_3 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_vowel ; 
 int /*<<< orphan*/  in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_remove_first_order_prefix(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 146 */
    if (z->c + 1 >= z->l || (z->p[z->c + 1] != 105 && z->p[z->c + 1] != 101)) return 0; /* substring, line 146 */
    among_var = find_among(z, a_3, 12);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 146 */
    switch (among_var) { /* among, line 146 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 147 */
                if (ret < 0) return ret;
            }
            z->I[1] = 1; /* $prefix = <integer expression>, line 147 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 147 */
            break;
        case 2:
            {   int ret = slice_del(z); /* delete, line 148 */
                if (ret < 0) return ret;
            }
            z->I[1] = 3; /* $prefix = <integer expression>, line 148 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 148 */
            break;
        case 3:
            z->I[1] = 1; /* $prefix = <integer expression>, line 149 */
            {   int ret = slice_from_s(z, 1, s_1); /* <-, line 149 */
                if (ret < 0) return ret;
            }
            z->I[0] -= 1; /* $measure -= <integer expression>, line 149 */
            break;
        case 4:
            z->I[1] = 3; /* $prefix = <integer expression>, line 150 */
            {   int ret = slice_from_s(z, 1, s_2); /* <-, line 150 */
                if (ret < 0) return ret;
            }
            z->I[0] -= 1; /* $measure -= <integer expression>, line 150 */
            break;
        case 5:
            z->I[1] = 1; /* $prefix = <integer expression>, line 151 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 151 */
            {   int c1 = z->c; /* or, line 151 */
                {   int c2 = z->c; /* and, line 151 */
                    if (in_grouping_U(z, g_vowel, 97, 117, 0)) goto lab1; /* grouping vowel, line 151 */
                    z->c = c2;
                    {   int ret = slice_from_s(z, 1, s_3); /* <-, line 151 */
                        if (ret < 0) return ret;
                    }
                }
                goto lab0;
            lab1:
                z->c = c1;
                {   int ret = slice_del(z); /* delete, line 151 */
                    if (ret < 0) return ret;
                }
            }
        lab0:
            break;
        case 6:
            z->I[1] = 3; /* $prefix = <integer expression>, line 152 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 152 */
            {   int c3 = z->c; /* or, line 152 */
                {   int c4 = z->c; /* and, line 152 */
                    if (in_grouping_U(z, g_vowel, 97, 117, 0)) goto lab3; /* grouping vowel, line 152 */
                    z->c = c4;
                    {   int ret = slice_from_s(z, 1, s_4); /* <-, line 152 */
                        if (ret < 0) return ret;
                    }
                }
                goto lab2;
            lab3:
                z->c = c3;
                {   int ret = slice_del(z); /* delete, line 152 */
                    if (ret < 0) return ret;
                }
            }
        lab2:
            break;
    }
    return 1;
}