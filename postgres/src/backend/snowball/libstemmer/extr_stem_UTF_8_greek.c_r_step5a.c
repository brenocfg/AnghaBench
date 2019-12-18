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
struct SN_env {int l; int c; int lb; int ket; int* p; size_t bra; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_40 ; 
 int /*<<< orphan*/  a_41 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_72 ; 
 int /*<<< orphan*/  s_73 ; 
 int /*<<< orphan*/  s_74 ; 
 int /*<<< orphan*/  s_75 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5a(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* do, line 424 */
        if (!(eq_s_b(z, 10, s_72))) goto lab0; /* literal, line 424 */
        if (z->c > z->lb) goto lab0; /* atlimit, line 424 */
        {   int ret = slice_from_s(z, 8, s_73); /* <-, line 424 */
            if (ret < 0) return ret;
        }
    lab0:
        z->c = z->l - m1;
    }
    {   int m2 = z->l - z->c; (void)m2; /* do, line 425 */
        z->ket = z->c; /* [, line 426 */
        if (z->c - 9 <= z->lb || z->p[z->c - 1] != 181) goto lab1; /* substring, line 426 */
        if (!(find_among_b(z, a_40, 5))) goto lab1;
        z->bra = z->c; /* ], line 426 */
        {   int ret = slice_del(z); /* delete, line 427 */
            if (ret < 0) return ret;
        }
        z->B[0] = 0; /* unset test1, line 427 */
    lab1:
        z->c = z->l - m2;
    }
    z->ket = z->c; /* [, line 430 */
    if (!(eq_s_b(z, 6, s_74))) return 0; /* literal, line 430 */
    z->bra = z->c; /* ], line 430 */
    {   int ret = slice_del(z); /* delete, line 431 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 432 */
    z->ket = z->c; /* [, line 433 */
    if (!(find_among_b(z, a_41, 12))) return 0; /* substring, line 433 */
    z->bra = z->c; /* ], line 433 */
    if (z->c > z->lb) return 0; /* atlimit, line 433 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 435 */
    if (z->S[0] == 0) return -1; /* -> s, line 435 */
    {   int ret = slice_from_s(z, 4, s_75); /* <-, line 435 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 435 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}