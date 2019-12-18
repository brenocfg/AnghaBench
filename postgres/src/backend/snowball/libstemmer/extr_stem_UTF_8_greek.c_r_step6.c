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
struct SN_env {int l; int c; int ket; int bra; int /*<<< orphan*/ * B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_71 ; 
 int /*<<< orphan*/  a_72 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_106 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_step6(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* do, line 643 */
        z->ket = z->c; /* [, line 644 */
        if (!(find_among_b(z, a_71, 3))) goto lab0; /* substring, line 644 */
        z->bra = z->c; /* ], line 644 */
        {   int ret = slice_from_s(z, 4, s_106); /* <-, line 645 */
            if (ret < 0) return ret;
        }
    lab0:
        z->c = z->l - m1;
    }
    if (!(z->B[0])) return 0; /* Boolean test test1, line 648 */
    z->ket = z->c; /* [, line 649 */
    if (!(find_among_b(z, a_72, 84))) return 0; /* substring, line 649 */
    z->bra = z->c; /* ], line 649 */
    {   int ret = slice_del(z); /* delete, line 659 */
        if (ret < 0) return ret;
    }
    return 1;
}