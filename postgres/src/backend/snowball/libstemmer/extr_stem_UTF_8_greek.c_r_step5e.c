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
struct SN_env {int ket; int c; int lb; int* p; int bra; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_49 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_88 ; 
 int /*<<< orphan*/  s_89 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5e(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 513 */
    if (z->c - 11 <= z->lb || z->p[z->c - 1] != 181) return 0; /* substring, line 513 */
    if (!(find_among_b(z, a_49, 2))) return 0;
    z->bra = z->c; /* ], line 513 */
    {   int ret = slice_del(z); /* delete, line 515 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 516 */
    z->ket = z->c; /* [, line 517 */
    if (!(eq_s_b(z, 4, s_88))) return 0; /* literal, line 517 */
    z->bra = z->c; /* ], line 517 */
    if (z->c > z->lb) return 0; /* atlimit, line 517 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 517 */
    if (z->S[0] == 0) return -1; /* -> s, line 517 */
    {   int ret = slice_from_s(z, 10, s_89); /* <-, line 517 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 517 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}