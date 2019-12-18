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
struct SN_env {int ket; int c; int bra; int l; scalar_t__* S; int lb; int* p; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_59 ; 
 int /*<<< orphan*/  a_60 ; 
 int /*<<< orphan*/  a_61 ; 
 int /*<<< orphan*/  a_62 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_100 ; 
 int /*<<< orphan*/  s_101 ; 
 int /*<<< orphan*/  s_98 ; 
 int /*<<< orphan*/  s_99 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5i(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 581 */
    if (!(find_among_b(z, a_62, 3))) return 0; /* substring, line 581 */
    z->bra = z->c; /* ], line 581 */
    {   int ret = slice_del(z); /* delete, line 583 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 584 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 585 */
        z->ket = z->c; /* [, line 585 */
        if (!(eq_s_b(z, 8, s_98))) goto lab1; /* literal, line 585 */
        z->bra = z->c; /* ], line 585 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 585 */
        if (z->S[0] == 0) return -1; /* -> s, line 585 */
        {   int ret = slice_from_s(z, 4, s_99); /* <-, line 585 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 585 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int m2 = z->l - z->c; (void)m2; /* not, line 586 */
            z->ket = z->c; /* [, line 586 */
            if (z->c - 5 <= z->lb || (z->p[z->c - 1] != 134 && z->p[z->c - 1] != 135)) goto lab2; /* substring, line 586 */
            if (!(find_among_b(z, a_59, 2))) goto lab2;
            z->bra = z->c; /* ], line 586 */
            return 0;
        lab2:
            z->c = z->l - m2;
        }
        {   int m3 = z->l - z->c; (void)m3; /* or, line 590 */
            z->ket = z->c; /* [, line 587 */
            if (!(find_among_b(z, a_60, 10))) goto lab4; /* substring, line 587 */
            z->bra = z->c; /* ], line 587 */
            z->S[0] = slice_to(z, z->S[0]); /* -> s, line 589 */
            if (z->S[0] == 0) return -1; /* -> s, line 589 */
            {   int ret = slice_from_s(z, 4, s_100); /* <-, line 589 */
                if (ret < 0) return ret;
            }
            {   int ret;
                {   int saved_c = z->c;
                    ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 589 */
                    z->c = saved_c;
                }
                if (ret < 0) return ret;
            }
            goto lab3;
        lab4:
            z->c = z->l - m3;
            z->ket = z->c; /* [, line 591 */
            if (!(find_among_b(z, a_61, 44))) return 0; /* substring, line 591 */
            z->bra = z->c; /* ], line 591 */
            if (z->c > z->lb) return 0; /* atlimit, line 591 */
            z->S[0] = slice_to(z, z->S[0]); /* -> s, line 597 */
            if (z->S[0] == 0) return -1; /* -> s, line 597 */
            {   int ret = slice_from_s(z, 4, s_101); /* <-, line 597 */
                if (ret < 0) return ret;
            }
            {   int ret;
                {   int saved_c = z->c;
                    ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 597 */
                    z->c = saved_c;
                }
                if (ret < 0) return ret;
            }
        }
    lab3:
        ;
    }
lab0:
    return 1;
}