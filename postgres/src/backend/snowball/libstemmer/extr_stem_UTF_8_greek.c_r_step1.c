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
struct SN_env {scalar_t__* B; int /*<<< orphan*/  c; int /*<<< orphan*/  bra; int /*<<< orphan*/  ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_24 ; 
 int /*<<< orphan*/  s_25 ; 
 int /*<<< orphan*/  s_26 ; 
 int /*<<< orphan*/  s_27 ; 
 int /*<<< orphan*/  s_28 ; 
 int /*<<< orphan*/  s_29 ; 
 int /*<<< orphan*/  s_30 ; 
 int /*<<< orphan*/  s_31 ; 
 int /*<<< orphan*/  s_32 ; 
 int /*<<< orphan*/  s_33 ; 
 int /*<<< orphan*/  s_34 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_step1(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 168 */
    among_var = find_among_b(z, a_1, 40); /* substring, line 168 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 168 */
    switch (among_var) { /* among, line 168 */
        case 1:
            {   int ret = slice_from_s(z, 4, s_24); /* <-, line 169 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 6, s_25); /* <-, line 170 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 6, s_26); /* <-, line 171 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 4, s_27); /* <-, line 172 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 8, s_28); /* <-, line 173 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 6, s_29); /* <-, line 174 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 6, s_30); /* <-, line 175 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 6, s_31); /* <-, line 176 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 4, s_32); /* <-, line 177 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = slice_from_s(z, 12, s_33); /* <-, line 178 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int ret = slice_from_s(z, 10, s_34); /* <-, line 179 */
                if (ret < 0) return ret;
            }
            break;
    }
    z->B[0] = 0; /* unset test1, line 181 */
    return 1;
}