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
struct SN_env {int* I; int l; int c; scalar_t__ lb; char* p; } ;

/* Variables and functions */

__attribute__((used)) static int r_SUFFIX_I_OK(struct SN_env * z) { /* backwardmode */
    if (!(z->I[1] <= 2)) return 0; /* $(<integer expression> <= <integer expression>), line 93 */
    {   int m1 = z->l - z->c; (void)m1; /* not, line 128 */
        if (z->c <= z->lb || z->p[z->c - 1] != 's') goto lab0; /* literal, line 128 */
        z->c--;
        return 0;
    lab0:
        z->c = z->l - m1;
    }
    return 1;
}