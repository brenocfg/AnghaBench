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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_7 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_double (struct SN_env*) ; 
 int r_undouble (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_factive(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 133 */
    if (z->c <= z->lb || (z->p[z->c - 1] != 225 && z->p[z->c - 1] != 233)) return 0; /* substring, line 133 */
    if (!(find_among_b(z, a_7, 2))) return 0;
    z->bra = z->c; /* ], line 133 */
    {   int ret = r_R1(z); /* call R1, line 133 */
        if (ret <= 0) return ret;
    }
    {   int ret = r_double(z); /* call double, line 134 */
        if (ret <= 0) return ret;
    }
    {   int ret = slice_del(z); /* delete, line 137 */
        if (ret < 0) return ret;
    }
    {   int ret = r_undouble(z); /* call undouble, line 138 */
        if (ret <= 0) return ret;
    }
    return 1;
}