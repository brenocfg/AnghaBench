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
 int /*<<< orphan*/  a_7 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_tidy_up(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 186 */
    if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 6 || !((151011360 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 186 */
    among_var = find_among_b(z, a_7, 4);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 186 */
    switch (among_var) { /* among, line 186 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 190 */
                if (ret < 0) return ret;
            }
            z->ket = z->c; /* [, line 191 */
            if (z->c <= z->lb || z->p[z->c - 1] != 0xCE) return 0; /* literal, line 191 */
            z->c--;
            z->bra = z->c; /* ], line 191 */
            if (z->c <= z->lb || z->p[z->c - 1] != 0xCE) return 0; /* literal, line 191 */
            z->c--;
            {   int ret = slice_del(z); /* delete, line 191 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (z->c <= z->lb || z->p[z->c - 1] != 0xCE) return 0; /* literal, line 194 */
            z->c--;
            {   int ret = slice_del(z); /* delete, line 194 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_del(z); /* delete, line 196 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}