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
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_remove_category_2(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 70 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 4 || !((262 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 70 */
    among_var = find_among_b(z, a_2, 3);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 70 */
    switch (among_var) { /* among, line 70 */
        case 1:
            {   int m1 = z->l - z->c; (void)m1; /* or, line 71 */
                if (!(eq_s_b(z, 6, s_2))) goto lab1; /* literal, line 71 */
                goto lab0;
            lab1:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 6, s_3))) goto lab2; /* literal, line 71 */
                goto lab0;
            lab2:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 6, s_4))) goto lab3; /* literal, line 71 */
                goto lab0;
            lab3:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 6, s_5))) return 0; /* literal, line 71 */
            }
        lab0:
            {   int ret = slice_del(z); /* delete, line 71 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (!(eq_s_b(z, 9, s_6))) return 0; /* literal, line 72 */
            {   int ret = slice_del(z); /* delete, line 72 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}