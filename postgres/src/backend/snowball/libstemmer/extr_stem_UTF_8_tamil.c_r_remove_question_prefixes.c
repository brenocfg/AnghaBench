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
struct SN_env {int bra; int c; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_fix_va_start (struct SN_env*) ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_remove_question_prefixes(struct SN_env * z) { /* forwardmode */
    z->bra = z->c; /* [, line 115 */
    if (!(eq_s(z, 3, s_12))) return 0; /* literal, line 115 */
    if (!(find_among(z, a_0, 10))) return 0; /* among, line 115 */
    if (!(eq_s(z, 3, s_13))) return 0; /* literal, line 115 */
    z->ket = z->c; /* ], line 115 */
    {   int ret = slice_del(z); /* delete, line 115 */
        if (ret < 0) return ret;
    }
    {   int c1 = z->c; /* do, line 116 */
        {   int ret = r_fix_va_start(z); /* call fix_va_start, line 116 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    return 1;
}