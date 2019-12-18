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
struct SN_env {int ket; int c; int bra; int l; int lb; int* p; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_12 ; 
 int /*<<< orphan*/  a_13 ; 
 int /*<<< orphan*/  a_14 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_43 ; 
 int /*<<< orphan*/  s_44 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_steps5(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 253 */
    if (!(find_among_b(z, a_14, 11))) return 0; /* substring, line 253 */
    z->bra = z->c; /* ], line 253 */
    {   int ret = slice_del(z); /* delete, line 256 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 257 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 261 */
        z->ket = z->c; /* [, line 258 */
        if (z->c - 3 <= z->lb || (z->p[z->c - 1] != 181 && z->p[z->c - 1] != 191)) goto lab1; /* substring, line 258 */
        if (!(find_among_b(z, a_12, 7))) goto lab1;
        z->bra = z->c; /* ], line 258 */
        if (z->c > z->lb) goto lab1; /* atlimit, line 258 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 260 */
        if (z->S[0] == 0) return -1; /* -> s, line 260 */
        {   int ret = slice_from_s(z, 2, s_43); /* <-, line 260 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 260 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 262 */
        if (!(find_among_b(z, a_13, 33))) return 0; /* substring, line 262 */
        z->bra = z->c; /* ], line 262 */
        if (z->c > z->lb) return 0; /* atlimit, line 262 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 266 */
        if (z->S[0] == 0) return -1; /* -> s, line 266 */
        {   int ret = slice_from_s(z, 6, s_44); /* <-, line 266 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 266 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
    }
lab0:
    return 1;
}