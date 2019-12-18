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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_step1(struct SN_env * z) { /* backwardmode */

    {   int mlimit1; /* setlimit, line 45 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 45 */
        if (!(find_among_b(z, a_0, 204))) { z->lb = mlimit1; return 0; } /* substring, line 45 */
        z->bra = z->c; /* ], line 45 */
        z->lb = mlimit1;
    }
    {   int ret = r_R1(z); /* call R1, line 45 */
        if (ret <= 0) return ret;
    }
    {   int ret = slice_del(z); /* delete, line 229 */
        if (ret < 0) return ret;
    }
    return 1;
}