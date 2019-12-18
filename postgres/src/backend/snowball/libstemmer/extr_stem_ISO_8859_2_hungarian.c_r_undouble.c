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
struct SN_env {int c; int lb; int ket; int l; int bra; } ;

/* Variables and functions */
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_undouble(struct SN_env * z) { /* backwardmode */
    if (z->c <= z->lb) return 0;
    z->c--; /* next, line 73 */
    z->ket = z->c; /* [, line 73 */
    {   int ret = z->c - 1; /* hop, line 73 */
        if (z->lb > ret || ret > z->l) return 0;
        z->c = ret;
    }
    z->bra = z->c; /* ], line 73 */
    {   int ret = slice_del(z); /* delete, line 73 */
        if (ret < 0) return ret;
    }
    return 1;
}