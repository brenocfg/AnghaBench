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
struct SN_env {int /*<<< orphan*/  c; int /*<<< orphan*/  bra; int /*<<< orphan*/  ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_v_ending (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_case(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 87 */
    if (!(find_among_b(z, a_4, 44))) return 0; /* substring, line 87 */
    z->bra = z->c; /* ], line 87 */
    {   int ret = r_R1(z); /* call R1, line 87 */
        if (ret <= 0) return ret;
    }
    {   int ret = slice_del(z); /* delete, line 111 */
        if (ret < 0) return ret;
    }
    {   int ret = r_v_ending(z); /* call v_ending, line 112 */
        if (ret <= 0) return ret;
    }
    return 1;
}