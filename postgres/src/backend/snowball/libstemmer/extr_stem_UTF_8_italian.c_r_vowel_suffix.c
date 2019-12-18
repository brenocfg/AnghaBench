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
struct SN_env {int l; int c; int ket; int bra; int lb; char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_AEIO ; 
 int /*<<< orphan*/  g_CG ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_RV (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_vowel_suffix(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* try, line 171 */
        z->ket = z->c; /* [, line 172 */
        if (in_grouping_b_U(z, g_AEIO, 97, 242, 0)) { z->c = z->l - m1; goto lab0; } /* grouping AEIO, line 172 */
        z->bra = z->c; /* ], line 172 */
        {   int ret = r_RV(z); /* call RV, line 172 */
            if (ret == 0) { z->c = z->l - m1; goto lab0; }
            if (ret < 0) return ret;
        }
        {   int ret = slice_del(z); /* delete, line 172 */
            if (ret < 0) return ret;
        }
        z->ket = z->c; /* [, line 173 */
        if (z->c <= z->lb || z->p[z->c - 1] != 'i') { z->c = z->l - m1; goto lab0; } /* literal, line 173 */
        z->c--;
        z->bra = z->c; /* ], line 173 */
        {   int ret = r_RV(z); /* call RV, line 173 */
            if (ret == 0) { z->c = z->l - m1; goto lab0; }
            if (ret < 0) return ret;
        }
        {   int ret = slice_del(z); /* delete, line 173 */
            if (ret < 0) return ret;
        }
    lab0:
        ;
    }
    {   int m2 = z->l - z->c; (void)m2; /* try, line 175 */
        z->ket = z->c; /* [, line 176 */
        if (z->c <= z->lb || z->p[z->c - 1] != 'h') { z->c = z->l - m2; goto lab1; } /* literal, line 176 */
        z->c--;
        z->bra = z->c; /* ], line 176 */
        if (in_grouping_b_U(z, g_CG, 99, 103, 0)) { z->c = z->l - m2; goto lab1; } /* grouping CG, line 176 */
        {   int ret = r_RV(z); /* call RV, line 176 */
            if (ret == 0) { z->c = z->l - m2; goto lab1; }
            if (ret < 0) return ret;
        }
        {   int ret = slice_del(z); /* delete, line 176 */
            if (ret < 0) return ret;
        }
    lab1:
        ;
    }
    return 1;
}