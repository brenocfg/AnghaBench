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
 int /*<<< orphan*/  a_3 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
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
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_2(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 58 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((815616 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 58 */
    among_var = find_among_b(z, a_3, 20);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 58 */
    {   int ret = r_R1(z); /* call R1, line 58 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 58 */
        case 1:
            {   int ret = slice_from_s(z, 4, s_6); /* <-, line 59 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 4, s_7); /* <-, line 60 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 4, s_8); /* <-, line 61 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 4, s_9); /* <-, line 62 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 3, s_10); /* <-, line 63 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 1, s_11); /* <-, line 64 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 3, s_12); /* <-, line 66 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 3, s_13); /* <-, line 68 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 2, s_14); /* <-, line 69 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = slice_from_s(z, 3, s_15); /* <-, line 72 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int ret = slice_from_s(z, 3, s_16); /* <-, line 74 */
                if (ret < 0) return ret;
            }
            break;
        case 12:
            {   int ret = slice_from_s(z, 3, s_17); /* <-, line 76 */
                if (ret < 0) return ret;
            }
            break;
        case 13:
            {   int ret = slice_from_s(z, 3, s_18); /* <-, line 77 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}