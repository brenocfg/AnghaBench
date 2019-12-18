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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_5 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_valid_LI ; 
 int /*<<< orphan*/  in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R1 (struct SN_env*) ; 
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
 int /*<<< orphan*/  s_20 ; 
 int /*<<< orphan*/  s_21 ; 
 int /*<<< orphan*/  s_22 ; 
 int /*<<< orphan*/  s_9 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_2(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 100 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((815616 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 100 */
    among_var = find_among_b(z, a_5, 24);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 100 */
    {   int ret = r_R1(z); /* call R1, line 100 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 100 */
        case 1:
            {   int ret = slice_from_s(z, 4, s_9); /* <-, line 101 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 4, s_10); /* <-, line 102 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 4, s_11); /* <-, line 103 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 4, s_12); /* <-, line 104 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 3, s_13); /* <-, line 105 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 3, s_14); /* <-, line 107 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 3, s_15); /* <-, line 109 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 2, s_16); /* <-, line 111 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 3, s_17); /* <-, line 112 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = slice_from_s(z, 3, s_18); /* <-, line 114 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int ret = slice_from_s(z, 3, s_19); /* <-, line 116 */
                if (ret < 0) return ret;
            }
            break;
        case 12:
            {   int ret = slice_from_s(z, 3, s_20); /* <-, line 118 */
                if (ret < 0) return ret;
            }
            break;
        case 13:
            if (z->c <= z->lb || z->p[z->c - 1] != 'l') return 0; /* literal, line 119 */
            z->c--;
            {   int ret = slice_from_s(z, 2, s_21); /* <-, line 119 */
                if (ret < 0) return ret;
            }
            break;
        case 14:
            {   int ret = slice_from_s(z, 4, s_22); /* <-, line 121 */
                if (ret < 0) return ret;
            }
            break;
        case 15:
            if (in_grouping_b_U(z, g_valid_LI, 99, 116, 0)) return 0; /* grouping valid_LI, line 122 */
            {   int ret = slice_del(z); /* delete, line 122 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}