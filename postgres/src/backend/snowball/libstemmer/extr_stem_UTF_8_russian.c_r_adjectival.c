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
struct SN_env {int l; int c; int ket; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_adjective (struct SN_env*) ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_adjectival(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int ret = r_adjective(z); /* call adjective, line 104 */
        if (ret <= 0) return ret;
    }
    {   int m1 = z->l - z->c; (void)m1; /* try, line 111 */
        z->ket = z->c; /* [, line 112 */
        among_var = find_among_b(z, a_2, 8); /* substring, line 112 */
        if (!(among_var)) { z->c = z->l - m1; goto lab0; }
        z->bra = z->c; /* ], line 112 */
        switch (among_var) { /* among, line 112 */
            case 1:
                {   int m2 = z->l - z->c; (void)m2; /* or, line 117 */
                    if (!(eq_s_b(z, 2, s_2))) goto lab2; /* literal, line 117 */
                    goto lab1;
                lab2:
                    z->c = z->l - m2;
                    if (!(eq_s_b(z, 2, s_3))) { z->c = z->l - m1; goto lab0; } /* literal, line 117 */
                }
            lab1:
                {   int ret = slice_del(z); /* delete, line 117 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z); /* delete, line 124 */
                    if (ret < 0) return ret;
                }
                break;
        }
    lab0:
        ;
    }
    return 1;
}