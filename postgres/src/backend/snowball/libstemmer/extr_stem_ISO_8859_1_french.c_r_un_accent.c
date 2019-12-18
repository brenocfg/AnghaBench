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
struct SN_env {int ket; int c; int l; int lb; int* p; size_t bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 scalar_t__ out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_32 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_un_accent(struct SN_env * z) { /* backwardmode */
    {   int i = 1;
        while(1) { /* atleast, line 222 */
            if (out_grouping_b(z, g_v, 97, 251, 0)) goto lab0; /* non v, line 222 */
            i--;
            continue;
        lab0:
            break;
        }
        if (i > 0) return 0;
    }
    z->ket = z->c; /* [, line 223 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 223 */
        if (z->c <= z->lb || z->p[z->c - 1] != 0xE9) goto lab2; /* literal, line 223 */
        z->c--;
        goto lab1;
    lab2:
        z->c = z->l - m1;
        if (z->c <= z->lb || z->p[z->c - 1] != 0xE8) return 0; /* literal, line 223 */
        z->c--;
    }
lab1:
    z->bra = z->c; /* ], line 223 */
    {   int ret = slice_from_s(z, 1, s_32); /* <-, line 223 */
        if (ret < 0) return ret;
    }
    return 1;
}