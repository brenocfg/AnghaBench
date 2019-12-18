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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; scalar_t__* S; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_v_b (struct SN_env*,scalar_t__) ; 
 int /*<<< orphan*/  g_c ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int slice_del (struct SN_env*) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_undouble(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 78 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 78 */
        if (in_grouping_b_U(z, g_c, 98, 122, 0)) { z->lb = mlimit1; return 0; } /* grouping c, line 78 */
        z->bra = z->c; /* ], line 78 */
        z->S[0] = slice_to(z, z->S[0]); /* -> ch, line 78 */
        if (z->S[0] == 0) return -1; /* -> ch, line 78 */
        z->lb = mlimit1;
    }
    if (!(eq_v_b(z, z->S[0]))) return 0; /* name ch, line 79 */
    {   int ret = slice_del(z); /* delete, line 80 */
        if (ret < 0) return ret;
    }
    return 1;
}