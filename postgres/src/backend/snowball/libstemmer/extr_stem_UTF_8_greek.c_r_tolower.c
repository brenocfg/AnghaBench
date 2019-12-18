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
struct SN_env {int l; int c; int ket; int bra; int /*<<< orphan*/  lb; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_16 ; 
 int /*<<< orphan*/  s_17 ; 
 int /*<<< orphan*/  s_18 ; 
 int /*<<< orphan*/  s_19 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_20 ; 
 int /*<<< orphan*/  s_21 ; 
 int /*<<< orphan*/  s_22 ; 
 int /*<<< orphan*/  s_23 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_tolower(struct SN_env * z) { /* backwardmode */
    int among_var;
    while(1) { /* repeat, line 115 */
        int m1 = z->l - z->c; (void)m1;
        z->ket = z->c; /* [, line 116 */
        among_var = find_among_b(z, a_0, 46); /* substring, line 116 */
        if (!(among_var)) goto lab0;
        z->bra = z->c; /* ], line 116 */
        switch (among_var) { /* among, line 116 */
            case 1:
                {   int ret = slice_from_s(z, 2, s_0); /* <-, line 117 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 2, s_1); /* <-, line 118 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 2, s_2); /* <-, line 119 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 2, s_3); /* <-, line 120 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = slice_from_s(z, 2, s_4); /* <-, line 121 */
                    if (ret < 0) return ret;
                }
                break;
            case 6:
                {   int ret = slice_from_s(z, 2, s_5); /* <-, line 122 */
                    if (ret < 0) return ret;
                }
                break;
            case 7:
                {   int ret = slice_from_s(z, 2, s_6); /* <-, line 123 */
                    if (ret < 0) return ret;
                }
                break;
            case 8:
                {   int ret = slice_from_s(z, 2, s_7); /* <-, line 124 */
                    if (ret < 0) return ret;
                }
                break;
            case 9:
                {   int ret = slice_from_s(z, 2, s_8); /* <-, line 125 */
                    if (ret < 0) return ret;
                }
                break;
            case 10:
                {   int ret = slice_from_s(z, 2, s_9); /* <-, line 126 */
                    if (ret < 0) return ret;
                }
                break;
            case 11:
                {   int ret = slice_from_s(z, 2, s_10); /* <-, line 127 */
                    if (ret < 0) return ret;
                }
                break;
            case 12:
                {   int ret = slice_from_s(z, 2, s_11); /* <-, line 128 */
                    if (ret < 0) return ret;
                }
                break;
            case 13:
                {   int ret = slice_from_s(z, 2, s_12); /* <-, line 129 */
                    if (ret < 0) return ret;
                }
                break;
            case 14:
                {   int ret = slice_from_s(z, 2, s_13); /* <-, line 130 */
                    if (ret < 0) return ret;
                }
                break;
            case 15:
                {   int ret = slice_from_s(z, 2, s_14); /* <-, line 131 */
                    if (ret < 0) return ret;
                }
                break;
            case 16:
                {   int ret = slice_from_s(z, 2, s_15); /* <-, line 132 */
                    if (ret < 0) return ret;
                }
                break;
            case 17:
                {   int ret = slice_from_s(z, 2, s_16); /* <-, line 133 */
                    if (ret < 0) return ret;
                }
                break;
            case 18:
                {   int ret = slice_from_s(z, 2, s_17); /* <-, line 134 */
                    if (ret < 0) return ret;
                }
                break;
            case 19:
                {   int ret = slice_from_s(z, 2, s_18); /* <-, line 135 */
                    if (ret < 0) return ret;
                }
                break;
            case 20:
                {   int ret = slice_from_s(z, 2, s_19); /* <-, line 136 */
                    if (ret < 0) return ret;
                }
                break;
            case 21:
                {   int ret = slice_from_s(z, 2, s_20); /* <-, line 137 */
                    if (ret < 0) return ret;
                }
                break;
            case 22:
                {   int ret = slice_from_s(z, 2, s_21); /* <-, line 138 */
                    if (ret < 0) return ret;
                }
                break;
            case 23:
                {   int ret = slice_from_s(z, 2, s_22); /* <-, line 139 */
                    if (ret < 0) return ret;
                }
                break;
            case 24:
                {   int ret = slice_from_s(z, 2, s_23); /* <-, line 140 */
                    if (ret < 0) return ret;
                }
                break;
            case 25:
                {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* next, line 162 */
                }
                break;
        }
        continue;
    lab0:
        z->c = z->l - m1;
        break;
    }
    return 1;
}