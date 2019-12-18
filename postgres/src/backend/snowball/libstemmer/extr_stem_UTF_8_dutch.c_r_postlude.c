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
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_postlude(struct SN_env * z) { /* forwardmode */
    int among_var;
    while(1) { /* repeat, line 75 */
        int c1 = z->c;
        z->bra = z->c; /* [, line 77 */
        if (z->c >= z->l || (z->p[z->c + 0] != 73 && z->p[z->c + 0] != 89)) among_var = 3; else /* substring, line 77 */
        among_var = find_among(z, a_1, 3);
        if (!(among_var)) goto lab0;
        z->ket = z->c; /* ], line 77 */
        switch (among_var) { /* among, line 77 */
            case 1:
                {   int ret = slice_from_s(z, 1, s_8); /* <-, line 78 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 1, s_9); /* <-, line 79 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* next, line 80 */
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