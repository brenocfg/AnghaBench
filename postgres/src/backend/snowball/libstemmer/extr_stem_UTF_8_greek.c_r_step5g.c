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
struct SN_env {int l; int c; int ket; int bra; scalar_t__* S; int lb; int* p; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_52 ; 
 int /*<<< orphan*/  a_53 ; 
 int /*<<< orphan*/  a_54 ; 
 int /*<<< orphan*/  a_55 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_94 ; 
 int /*<<< orphan*/  s_95 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5g(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* do, line 541 */
        z->ket = z->c; /* [, line 542 */
        if (!(find_among_b(z, a_52, 3))) goto lab0; /* substring, line 542 */
        z->bra = z->c; /* ], line 542 */
        {   int ret = slice_del(z); /* delete, line 543 */
            if (ret < 0) return ret;
        }
        z->B[0] = 0; /* unset test1, line 543 */
    lab0:
        z->c = z->l - m1;
    }
    z->ket = z->c; /* [, line 546 */
    if (!(find_among_b(z, a_55, 3))) return 0; /* substring, line 546 */
    z->bra = z->c; /* ], line 546 */
    {   int ret = slice_del(z); /* delete, line 548 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 549 */
    {   int m2 = z->l - z->c; (void)m2; /* or, line 552 */
        z->ket = z->c; /* [, line 550 */
        if (!(find_among_b(z, a_53, 6))) goto lab2; /* substring, line 550 */
        z->bra = z->c; /* ], line 550 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 551 */
        if (z->S[0] == 0) return -1; /* -> s, line 551 */
        {   int ret = slice_from_s(z, 4, s_94); /* <-, line 551 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 551 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab1;
    lab2:
        z->c = z->l - m2;
        z->ket = z->c; /* [, line 553 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] != 184) return 0; /* substring, line 553 */
        if (!(find_among_b(z, a_54, 5))) return 0;
        z->bra = z->c; /* ], line 553 */
        if (z->c > z->lb) return 0; /* atlimit, line 553 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 554 */
        if (z->S[0] == 0) return -1; /* -> s, line 554 */
        {   int ret = slice_from_s(z, 4, s_95); /* <-, line 554 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 554 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
    }
lab1:
    return 1;
}