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
 int /*<<< orphan*/  a_8 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_verb_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 176 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 176 */
        among_var = find_among_b(z, a_8, 96); /* substring, line 176 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 176 */
        z->lb = mlimit1;
    }
    switch (among_var) { /* among, line 176 */
        case 1:
            {   int m2 = z->l - z->c; (void)m2; /* try, line 179 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'u') { z->c = z->l - m2; goto lab0; } /* literal, line 179 */
                z->c--;
                {   int m_test3 = z->l - z->c; /* test, line 179 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'g') { z->c = z->l - m2; goto lab0; } /* literal, line 179 */
                    z->c--;
                    z->c = z->l - m_test3;
                }
            lab0:
                ;
            }
            z->bra = z->c; /* ], line 179 */
            {   int ret = slice_del(z); /* delete, line 179 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_del(z); /* delete, line 200 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}