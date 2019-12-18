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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; int l; unsigned char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_4 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 int /*<<< orphan*/  out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_verb_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 164 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 165 */
        among_var = find_among_b(z, a_4, 94); /* substring, line 165 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 165 */
        switch (among_var) { /* among, line 165 */
            case 1:
                {   int m2 = z->l - z->c; (void)m2; /* or, line 200 */
                    if (out_grouping_b(z, g_v, 97, 238, 0)) goto lab1; /* non v, line 200 */
                    goto lab0;
                lab1:
                    z->c = z->l - m2;
                    if (z->c <= z->lb || z->p[z->c - 1] != 'u') { z->lb = mlimit1; return 0; } /* literal, line 200 */
                    z->c--;
                }
            lab0:
                {   int ret = slice_del(z); /* delete, line 200 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z); /* delete, line 214 */
                    if (ret < 0) return ret;
                }
                break;
        }
        z->lb = mlimit1;
    }
    return 1;
}