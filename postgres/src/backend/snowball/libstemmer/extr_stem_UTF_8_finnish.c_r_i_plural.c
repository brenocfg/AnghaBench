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
 int /*<<< orphan*/  a_8 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_i_plural(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 155 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 155 */
        if (z->c <= z->lb || (z->p[z->c - 1] != 105 && z->p[z->c - 1] != 106)) { z->lb = mlimit1; return 0; } /* substring, line 155 */
        if (!(find_among_b(z, a_8, 2))) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 155 */
        z->lb = mlimit1;
    }
    {   int ret = slice_del(z); /* delete, line 159 */
        if (ret < 0) return ret;
    }
    return 1;
}