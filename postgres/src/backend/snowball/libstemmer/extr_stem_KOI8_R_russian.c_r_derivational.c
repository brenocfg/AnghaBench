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
 int /*<<< orphan*/  a_6 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_derivational(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 178 */
    if (z->c - 2 <= z->lb || (z->p[z->c - 1] != 212 && z->p[z->c - 1] != 216)) return 0; /* substring, line 178 */
    if (!(find_among_b(z, a_6, 2))) return 0;
    z->bra = z->c; /* ], line 178 */
    {   int ret = r_R2(z); /* call R2, line 178 */
        if (ret <= 0) return ret;
    }
    {   int ret = slice_del(z); /* delete, line 181 */
        if (ret < 0) return ret;
    }
    return 1;
}