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
struct SN_env {int l; int c; scalar_t__ lb; int* p; size_t ket; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_8 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int skip_utf8 (int*,size_t,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_un_double(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 218 */
        if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1069056 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 218 */
        if (!(find_among_b(z, a_8, 5))) return 0;
        z->c = z->l - m_test1;
    }
    z->ket = z->c; /* [, line 218 */
    {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
        if (ret < 0) return 0;
        z->c = ret; /* next, line 218 */
    }
    z->bra = z->c; /* ], line 218 */
    {   int ret = slice_del(z); /* delete, line 218 */
        if (ret < 0) return ret;
    }
    return 1;
}