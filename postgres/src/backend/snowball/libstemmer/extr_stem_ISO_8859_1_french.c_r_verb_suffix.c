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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; int l; char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_6 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_verb_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 181 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 182 */
        among_var = find_among_b(z, a_6, 38); /* substring, line 182 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 182 */
        switch (among_var) { /* among, line 182 */
            case 1:
                {   int ret = r_R2(z); /* call R2, line 184 */
                    if (ret == 0) { z->lb = mlimit1; return 0; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 184 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z); /* delete, line 192 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_del(z); /* delete, line 197 */
                    if (ret < 0) return ret;
                }
                {   int m2 = z->l - z->c; (void)m2; /* try, line 198 */
                    z->ket = z->c; /* [, line 198 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'e') { z->c = z->l - m2; goto lab0; } /* literal, line 198 */
                    z->c--;
                    z->bra = z->c; /* ], line 198 */
                    {   int ret = slice_del(z); /* delete, line 198 */
                        if (ret < 0) return ret;
                    }
                lab0:
                    ;
                }
                break;
        }
        z->lb = mlimit1;
    }
    return 1;
}