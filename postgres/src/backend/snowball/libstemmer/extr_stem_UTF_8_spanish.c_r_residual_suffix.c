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
struct SN_env {int ket; int c; int bra; int l; int lb; unsigned char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_9 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_RV (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_residual_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 205 */
    among_var = find_among_b(z, a_9, 8); /* substring, line 205 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 205 */
    switch (among_var) { /* among, line 205 */
        case 1:
            {   int ret = r_RV(z); /* call RV, line 208 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 208 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_RV(z); /* call RV, line 210 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 210 */
                if (ret < 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* try, line 210 */
                z->ket = z->c; /* [, line 210 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'u') { z->c = z->l - m1; goto lab0; } /* literal, line 210 */
                z->c--;
                z->bra = z->c; /* ], line 210 */
                {   int m_test2 = z->l - z->c; /* test, line 210 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'g') { z->c = z->l - m1; goto lab0; } /* literal, line 210 */
                    z->c--;
                    z->c = z->l - m_test2;
                }
                {   int ret = r_RV(z); /* call RV, line 210 */
                    if (ret == 0) { z->c = z->l - m1; goto lab0; }
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 210 */
                    if (ret < 0) return ret;
                }
            lab0:
                ;
            }
            break;
    }
    return 1;
}