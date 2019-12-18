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
struct SN_env {int ket; int c; int bra; int lb; int* p; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_63 ; 
 int /*<<< orphan*/  a_64 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_102 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_step5j(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 605 */
    if (!(find_among_b(z, a_63, 3))) return 0; /* substring, line 605 */
    z->bra = z->c; /* ], line 605 */
    {   int ret = slice_del(z); /* delete, line 606 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 606 */
    z->ket = z->c; /* [, line 608 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] != 189) return 0; /* substring, line 608 */
    if (!(find_among_b(z, a_64, 6))) return 0;
    z->bra = z->c; /* ], line 608 */
    if (z->c > z->lb) return 0; /* atlimit, line 608 */
    z->S[0] = slice_to(z, z->S[0]); /* -> s, line 609 */
    if (z->S[0] == 0) return -1; /* -> s, line 609 */
    {   int ret = slice_from_s(z, 4, s_102); /* <-, line 609 */
        if (ret < 0) return ret;
    }
    {   int ret;
        {   int saved_c = z->c;
            ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 609 */
            z->c = saved_c;
        }
        if (ret < 0) return ret;
    }
    return 1;
}