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
struct SN_env {int ket; int c; int lb; int* p; int bra; scalar_t__* S; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_33 ; 
 int /*<<< orphan*/  a_34 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_67 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step2c(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 384 */
    if (z->c - 9 <= z->lb || (z->p[z->c - 1] != 131 && z->p[z->c - 1] != 189)) return 0; /* substring, line 384 */
    if (!(find_among_b(z, a_33, 2))) return 0;
    z->bra = z->c; /* ], line 384 */
    {   int ret = slice_del(z); /* delete, line 385 */
        if (ret < 0) return ret;
    }
    z->ket = z->c; /* [, line 387 */
    if (!(find_among_b(z, a_34, 15))) return 0; /* substring, line 387 */
    z->bra = z->c; /* ], line 387 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 389 */
    if (z->S[0] == 0) return -1; /* -> s, line 389 */
    {   int ret = slice_from_s(z, 6, s_67); /* <-, line 389 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 389 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}