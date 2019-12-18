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
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_verb(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 139 */
    among_var = find_among_b(z, a_4, 46); /* substring, line 139 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 139 */
    switch (among_var) { /* among, line 139 */
        case 1:
            {   int m1 = z->l - z->c; (void)m1; /* or, line 145 */
                if (!(eq_s_b(z, 2, s_4))) goto lab1; /* literal, line 145 */
                goto lab0;
            lab1:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 2, s_5))) return 0; /* literal, line 145 */
            }
        lab0:
            {   int ret = slice_del(z); /* delete, line 145 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_del(z); /* delete, line 153 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}