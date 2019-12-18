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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_19 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_Suffix_Verb_Step2b(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 469 */
    if (z->c - 3 <= z->lb || (z->p[z->c - 1] != 133 && z->p[z->c - 1] != 167)) return 0; /* substring, line 469 */
    if (!(find_among_b(z, a_19, 2))) return 0;
    z->bra = z->c; /* ], line 469 */
    if (!(len_utf8(z->p) >= 5)) return 0; /* $(<integer expression> >= <integer expression>), line 470 */
    {   int ret = slice_del(z); /* delete, line 470 */
        if (ret < 0) return ret;
    }
    return 1;
}