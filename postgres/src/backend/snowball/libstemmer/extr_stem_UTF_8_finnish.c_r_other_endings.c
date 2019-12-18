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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_7 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_5 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_other_endings(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 143 */
        if (z->c < z->I[1]) return 0;
        mlimit1 = z->lb; z->lb = z->I[1];
        z->ket = z->c; /* [, line 143 */
        among_var = find_among_b(z, a_7, 14); /* substring, line 143 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 143 */
        z->lb = mlimit1;
    }
    switch (among_var) { /* among, line 144 */
        case 1:
            {   int m2 = z->l - z->c; (void)m2; /* not, line 147 */
                if (!(eq_s_b(z, 2, s_5))) goto lab0; /* literal, line 147 */
                return 0;
            lab0:
                z->c = z->l - m2;
            }
            break;
    }
    {   int ret = slice_del(z); /* delete, line 152 */
        if (ret < 0) return ret;
    }
    return 1;
}