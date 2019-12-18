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
struct SN_env {int ket; int c; int bra; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_remove_category_1(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 54 */
    among_var = find_among_b(z, a_0, 17); /* substring, line 54 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 54 */
    switch (among_var) { /* among, line 54 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 58 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int m1 = z->l - z->c; (void)m1; /* or, line 59 */
                {   int m2 = z->l - z->c; (void)m2; /* or, line 59 */
                    if (!(eq_s_b(z, 3, s_0))) goto lab3; /* literal, line 59 */
                    goto lab2;
                lab3:
                    z->c = z->l - m2;
                    if (!(eq_s_b(z, 3, s_1))) goto lab1; /* literal, line 59 */
                }
            lab2:
                goto lab0;
            lab1:
                z->c = z->l - m1;
                {   int ret = slice_del(z); /* delete, line 59 */
                    if (ret < 0) return ret;
                }
            }
        lab0:
            break;
    }
    return 1;
}