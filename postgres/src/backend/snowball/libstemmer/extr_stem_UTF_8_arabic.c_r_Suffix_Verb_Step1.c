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
struct SN_env {int /*<<< orphan*/  p; int /*<<< orphan*/  c; int /*<<< orphan*/  bra; int /*<<< orphan*/  ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_17 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int /*<<< orphan*/ ) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_Suffix_Verb_Step1(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 452 */
    among_var = find_among_b(z, a_17, 12); /* substring, line 452 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 452 */
    switch (among_var) { /* among, line 452 */
        case 1:
            if (!(len_utf8(z->p) >= 4)) return 0; /* $(<integer expression> >= <integer expression>), line 453 */
            {   int ret = slice_del(z); /* delete, line 453 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (!(len_utf8(z->p) >= 5)) return 0; /* $(<integer expression> >= <integer expression>), line 454 */
            {   int ret = slice_del(z); /* delete, line 454 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            if (!(len_utf8(z->p) >= 6)) return 0; /* $(<integer expression> >= <integer expression>), line 455 */
            {   int ret = slice_del(z); /* delete, line 455 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}