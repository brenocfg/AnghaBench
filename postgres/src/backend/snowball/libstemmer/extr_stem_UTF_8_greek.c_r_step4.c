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
struct SN_env {int ket; int c; int bra; int l; scalar_t__* S; int lb; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_38 ; 
 int /*<<< orphan*/  a_39 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_70 ; 
 int /*<<< orphan*/  s_71 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step4(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 410 */
    if (!(find_among_b(z, a_38, 4))) return 0; /* substring, line 410 */
    z->bra = z->c; /* ], line 410 */
    {   int ret = slice_del(z); /* delete, line 411 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 411 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 413 */
        z->ket = z->c; /* [, line 413 */
        if (in_grouping_b_U(z, g_v, 945, 969, 0)) goto lab1; /* grouping v, line 413 */
        z->bra = z->c; /* ], line 413 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 413 */
        if (z->S[0] == 0) return -1; /* -> s, line 413 */
        {   int ret = slice_from_s(z, 4, s_70); /* <-, line 413 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 413 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 414 */
    }
lab0:
    if (!(find_among_b(z, a_39, 36))) return 0; /* substring, line 414 */
    z->bra = z->c; /* ], line 414 */
    if (z->c > z->lb) return 0; /* atlimit, line 414 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 419 */
    if (z->S[0] == 0) return -1; /* -> s, line 419 */
    {   int ret = slice_from_s(z, 4, s_71); /* <-, line 419 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 419 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}