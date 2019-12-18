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
struct SN_env {int c; int* I; int lb; int ket; int* p; int bra; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_5 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_i_verb_suffix(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 170 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 171 */
        if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((68944418 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->lb = mlimit1; return 0; } /* substring, line 171 */
        if (!(find_among_b(z, a_5, 35))) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 171 */
        {   int m2 = z->l - z->c; (void)m2; /* not, line 177 */
            if (z->c <= z->lb || z->p[z->c - 1] != 'H') goto lab0; /* literal, line 177 */
            z->c--;
            { z->lb = mlimit1; return 0; }
        lab0:
            z->c = z->l - m2;
        }
        if (out_grouping_b_U(z, g_v, 97, 251, 0)) { z->lb = mlimit1; return 0; } /* non v, line 177 */
        {   int ret = slice_del(z); /* delete, line 177 */
            if (ret < 0) return ret;
        }
        z->lb = mlimit1;
    }
    return 1;
}