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
 int /*<<< orphan*/  a_1 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_noun_sfx(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 104 */
    among_var = find_among_b(z, a_1, 16); /* substring, line 104 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 104 */
    switch (among_var) { /* among, line 104 */
        case 1:
            {   int ret = r_R1(z); /* call R1, line 108 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 108 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 110 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 110 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}