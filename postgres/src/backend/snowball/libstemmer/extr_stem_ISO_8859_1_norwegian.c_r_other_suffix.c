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
struct SN_env {int c; int* I; int lb; int ket; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_other_suffix(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 63 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 63 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((4718720 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->lb = mlimit1; return 0; } /* substring, line 63 */
        if (!(find_among_b(z, a_2, 11))) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 63 */
        z->lb = mlimit1;
    }
    {   int ret = slice_del(z); /* delete, line 67 */
        if (ret < 0) return ret;
    }
    return 1;
}