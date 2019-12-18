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
struct SN_env {int bra; int c; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_10 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_27 ; 
 int /*<<< orphan*/  s_28 ; 
 int /*<<< orphan*/  s_29 ; 
 int /*<<< orphan*/  s_30 ; 
 int /*<<< orphan*/  s_31 ; 
 int /*<<< orphan*/  s_32 ; 
 int /*<<< orphan*/  s_33 ; 
 int /*<<< orphan*/  s_34 ; 
 int /*<<< orphan*/  s_35 ; 
 int /*<<< orphan*/  s_36 ; 
 int /*<<< orphan*/  s_37 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_exception1(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 170 */
    if (z->c + 2 >= z->l || z->p[z->c + 2] >> 5 != 3 || !((42750482 >> (z->p[z->c + 2] & 0x1f)) & 1)) return 0; /* substring, line 170 */
    among_var = find_among(z, a_10, 18);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 170 */
    if (z->c < z->l) return 0; /* atlimit, line 170 */
    switch (among_var) { /* among, line 170 */
        case 1:
            {   int ret = slice_from_s(z, 3, s_27); /* <-, line 174 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 3, s_28); /* <-, line 175 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 3, s_29); /* <-, line 176 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 3, s_30); /* <-, line 177 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 3, s_31); /* <-, line 178 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 3, s_32); /* <-, line 182 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 5, s_33); /* <-, line 183 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 4, s_34); /* <-, line 184 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 5, s_35); /* <-, line 185 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = slice_from_s(z, 4, s_36); /* <-, line 186 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int ret = slice_from_s(z, 5, s_37); /* <-, line 187 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}