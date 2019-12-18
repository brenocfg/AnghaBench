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
 int /*<<< orphan*/  a_4 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_remove_second_order_prefix(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 162 */
    if (z->c + 1 >= z->l || z->p[z->c + 1] != 101) return 0; /* substring, line 162 */
    among_var = find_among(z, a_4, 6);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 162 */
    switch (among_var) { /* among, line 162 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 163 */
                if (ret < 0) return ret;
            }
            z->I[1] = 2; /* $prefix = <integer expression>, line 163 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 163 */
            break;
        case 2:
            {   int ret = slice_from_s(z, 4, s_5); /* <-, line 164 */
                if (ret < 0) return ret;
            }
            z->I[0] -= 1; /* $measure -= <integer expression>, line 164 */
            break;
        case 3:
            {   int ret = slice_del(z); /* delete, line 165 */
                if (ret < 0) return ret;
            }
            z->I[1] = 4; /* $prefix = <integer expression>, line 165 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 165 */
            break;
        case 4:
            {   int ret = slice_from_s(z, 4, s_6); /* <-, line 166 */
                if (ret < 0) return ret;
            }
            z->I[1] = 4; /* $prefix = <integer expression>, line 166 */
            z->I[0] -= 1; /* $measure -= <integer expression>, line 166 */
            break;
    }
    return 1;
}