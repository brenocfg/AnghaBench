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
struct SN_env {int l; int c; scalar_t__ lb; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_16 ; 
 int /*<<< orphan*/  s_17 ; 

__attribute__((used)) static int r_is_reserved_word(struct SN_env * z) { /* backwardmode */
    if (!(eq_s_b(z, 2, s_16))) return 0; /* literal, line 440 */
    {   int m1 = z->l - z->c; (void)m1; /* try, line 440 */
        if (!(eq_s_b(z, 3, s_17))) { z->c = z->l - m1; goto lab0; } /* literal, line 440 */
    lab0:
        ;
    }
    if (z->c > z->lb) return 0; /* atlimit, line 440 */
    return 1;
}