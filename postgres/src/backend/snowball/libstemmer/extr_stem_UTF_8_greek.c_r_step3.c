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
struct SN_env {int ket; int c; int bra; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_37 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_69 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step3(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 403 */
    if (!(find_among_b(z, a_37, 3))) return 0; /* substring, line 403 */
    z->bra = z->c; /* ], line 403 */
    {   int ret = slice_del(z); /* delete, line 404 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 404 */
    z->ket = z->c; /* [, line 406 */
    if (in_grouping_b_U(z, g_v, 945, 969, 0)) return 0; /* grouping v, line 406 */
    z->bra = z->c; /* ], line 406 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 406 */
    if (z->S[0] == 0) return -1; /* -> s, line 406 */
    {   int ret = slice_from_s(z, 2, s_69); /* <-, line 406 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 406 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}