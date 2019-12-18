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
 int /*<<< orphan*/  a_3 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_RV (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_verb_sfx(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 130 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((282896 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 130 */
    among_var = find_among_b(z, a_3, 12);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 130 */
    switch (among_var) { /* among, line 130 */
        case 1:
            {   int ret = r_RV(z); /* call RV, line 133 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 133 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R1(z); /* call R1, line 138 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 138 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}