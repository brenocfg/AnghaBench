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
struct SN_env {int ket; int c; int lb; int* p; int bra; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_5 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_Step_4(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 92 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((3961384 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 92 */
    among_var = find_among_b(z, a_5, 19);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 92 */
    {   int ret = r_R2(z); /* call R2, line 92 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 92 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 95 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int m1 = z->l - z->c; (void)m1; /* or, line 96 */
                if (z->c <= z->lb || z->p[z->c - 1] != 's') goto lab1; /* literal, line 96 */
                z->c--;
                goto lab0;
            lab1:
                z->c = z->l - m1;
                if (z->c <= z->lb || z->p[z->c - 1] != 't') return 0; /* literal, line 96 */
                z->c--;
            }
        lab0:
            {   int ret = slice_del(z); /* delete, line 96 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}