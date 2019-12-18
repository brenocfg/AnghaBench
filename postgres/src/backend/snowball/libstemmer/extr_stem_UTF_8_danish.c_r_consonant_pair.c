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
struct SN_env {int l; int c; scalar_t__* I; int lb; scalar_t__ ket; int* p; size_t bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int skip_utf8 (int*,size_t,int,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_consonant_pair(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 57 */

        {   int mlimit2; /* setlimit, line 58 */
            if (z->c < z->I[0]) return 0;
            mlimit2 = z->lb; z->lb = z->I[0];
            z->ket = z->c; /* [, line 58 */
            if (z->c - 1 <= z->lb || (z->p[z->c - 1] != 100 && z->p[z->c - 1] != 116)) { z->lb = mlimit2; return 0; } /* substring, line 58 */
            if (!(find_among_b(z, a_1, 4))) { z->lb = mlimit2; return 0; }
            z->bra = z->c; /* ], line 58 */
            z->lb = mlimit2;
        }
        z->c = z->l - m_test1;
    }
    {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
        if (ret < 0) return 0;
        z->c = ret; /* next, line 64 */
    }
    z->bra = z->c; /* ], line 64 */
    {   int ret = slice_del(z); /* delete, line 64 */
        if (ret < 0) return ret;
    }
    return 1;
}