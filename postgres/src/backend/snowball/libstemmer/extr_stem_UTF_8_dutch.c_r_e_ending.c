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
struct SN_env {int* B; int ket; int c; int lb; char* p; int bra; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 scalar_t__ out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R1 (struct SN_env*) ; 
 int r_undouble (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_e_ending(struct SN_env * z) { /* backwardmode */
    z->B[0] = 0; /* unset e_found, line 95 */
    z->ket = z->c; /* [, line 96 */
    if (z->c <= z->lb || z->p[z->c - 1] != 'e') return 0; /* literal, line 96 */
    z->c--;
    z->bra = z->c; /* ], line 96 */
    {   int ret = r_R1(z); /* call R1, line 96 */
        if (ret <= 0) return ret;
    }
    {   int m_test1 = z->l - z->c; /* test, line 96 */
        if (out_grouping_b_U(z, g_v, 97, 232, 0)) return 0; /* non v, line 96 */
        z->c = z->l - m_test1;
    }
    {   int ret = slice_del(z); /* delete, line 96 */
        if (ret < 0) return ret;
    }
    z->B[0] = 1; /* set e_found, line 97 */
    {   int ret = r_undouble(z); /* call undouble, line 98 */
        if (ret <= 0) return ret;
    }
    return 1;
}