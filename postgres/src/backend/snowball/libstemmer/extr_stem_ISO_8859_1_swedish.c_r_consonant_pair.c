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
struct SN_env {int c; int* I; int lb; int l; int* p; size_t ket; size_t bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_consonant_pair(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 50 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        {   int m2 = z->l - z->c; (void)m2; /* and, line 52 */
            if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1064976 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->lb = mlimit1; return 0; } /* among, line 51 */
            if (!(find_among_b(z, a_1, 7))) { z->lb = mlimit1; return 0; }
            z->c = z->l - m2;
            z->ket = z->c; /* [, line 52 */
            if (z->c <= z->lb) { z->lb = mlimit1; return 0; }
            z->c--; /* next, line 52 */
            z->bra = z->c; /* ], line 52 */
            {   int ret = slice_del(z); /* delete, line 52 */
                if (ret < 0) return ret;
            }
        }
        z->lb = mlimit1;
    }
    return 1;
}