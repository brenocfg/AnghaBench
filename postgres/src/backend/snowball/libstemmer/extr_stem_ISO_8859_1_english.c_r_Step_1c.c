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
 scalar_t__ out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_8 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_1c(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 94 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 94 */
        if (z->c <= z->lb || z->p[z->c - 1] != 'y') goto lab1; /* literal, line 94 */
        z->c--;
        goto lab0;
    lab1:
        z->c = z->l - m1;
        if (z->c <= z->lb || z->p[z->c - 1] != 'Y') return 0; /* literal, line 94 */
        z->c--;
    }
lab0:
    z->bra = z->c; /* ], line 94 */
    if (out_grouping_b(z, g_v, 97, 121, 0)) return 0; /* non v, line 95 */
    /* not, line 95 */
    if (z->c > z->lb) goto lab2; /* atlimit, line 95 */
    return 0;
lab2:
    {   int ret = slice_from_s(z, 1, s_8); /* <-, line 96 */
        if (ret < 0) return ret;
    }
    return 1;
}