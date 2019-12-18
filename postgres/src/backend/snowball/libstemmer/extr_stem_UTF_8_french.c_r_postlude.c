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
struct SN_env {int c; int bra; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_postlude(struct SN_env * z) { /* forwardmode */
    int among_var;
    while(1) { /* repeat, line 79 */
        int c1 = z->c;
        z->bra = z->c; /* [, line 81 */
        if (z->c >= z->l || z->p[z->c + 0] >> 5 != 2 || !((35652352 >> (z->p[z->c + 0] & 0x1f)) & 1)) among_var = 7; else /* substring, line 81 */
        among_var = find_among(z, a_1, 7);
        if (!(among_var)) goto lab0;
        z->ket = z->c; /* ], line 81 */
        switch (among_var) { /* among, line 81 */
            case 1:
                {   int ret = slice_from_s(z, 1, s_9); /* <-, line 82 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 1, s_10); /* <-, line 83 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 1, s_11); /* <-, line 84 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 2, s_12); /* <-, line 85 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = slice_from_s(z, 2, s_13); /* <-, line 86 */
                    if (ret < 0) return ret;
                }
                break;
            case 6:
                {   int ret = slice_del(z); /* delete, line 87 */
                    if (ret < 0) return ret;
                }
                break;
            case 7:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* next, line 88 */
                }
                break;
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}