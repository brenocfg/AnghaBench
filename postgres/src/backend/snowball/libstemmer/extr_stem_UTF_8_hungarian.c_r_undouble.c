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
struct SN_env {int c; int ket; int bra; int /*<<< orphan*/  l; int /*<<< orphan*/  lb; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int skip_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_undouble(struct SN_env * z) { /* backwardmode */
    {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
        if (ret < 0) return 0;
        z->c = ret; /* next, line 73 */
    }
    z->ket = z->c; /* [, line 73 */
    {   int ret = skip_utf8(z->p, z->c, z->lb, z->l, - 1); /* hop, line 73 */
        if (ret < 0) return 0;
        z->c = ret;
    }
    z->bra = z->c; /* ], line 73 */
    {   int ret = slice_del(z); /* delete, line 73 */
        if (ret < 0) return ret;
    }
    return 1;
}