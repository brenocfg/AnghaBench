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
 int /*<<< orphan*/  a_2 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_fix_conflicts(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 307 */
    if (z->c - 3 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((2621472 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 307 */
    among_var = find_among_b(z, a_2, 11);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 307 */
    switch (among_var) { /* among, line 307 */
        case 1:
            {   int ret = slice_from_s(z, 5, s_0); /* <-, line 309 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 5, s_1); /* <-, line 314 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 7, s_2); /* <-, line 319 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 4, s_3); /* <-, line 322 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 4, s_4); /* <-, line 324 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 6, s_5); /* <-, line 327 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 6, s_6); /* <-, line 328 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 6, s_7); /* <-, line 331 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}