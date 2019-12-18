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
struct SN_env {int ket; int c; int l; int lb; char* p; size_t bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  s_5 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_1c(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 52 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 52 */
        if (z->c <= z->lb || z->p[z->c - 1] != 'y') goto lab1; /* literal, line 52 */
        z->c--;
        goto lab0;
    lab1:
        z->c = z->l - m1;
        if (z->c <= z->lb || z->p[z->c - 1] != 'Y') return 0; /* literal, line 52 */
        z->c--;
    }
lab0:
    z->bra = z->c; /* ], line 52 */
    {    /* gopast */ /* grouping v, line 53 */
        int ret = out_grouping_b_U(z, g_v, 97, 121, 1);
        if (ret < 0) return 0;
        z->c -= ret;
    }
    {   int ret = slice_from_s(z, 1, s_5); /* <-, line 54 */
        if (ret < 0) return ret;
    }
    return 1;
}