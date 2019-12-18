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
struct SN_env {int* I; int l; int c; int* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int /*<<< orphan*/  find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $p1 = <integer expression>, line 46 */
    {   int c1 = z->c; /* or, line 51 */
        if (in_grouping_U(z, g_v, 97, 369, 0)) goto lab1; /* grouping v, line 48 */
        if (in_grouping_U(z, g_v, 97, 369, 1) < 0) goto lab1; /* goto */ /* non v, line 48 */
        {   int c2 = z->c; /* or, line 49 */
            if (z->c + 1 >= z->l || z->p[z->c + 1] >> 5 != 3 || !((101187584 >> (z->p[z->c + 1] & 0x1f)) & 1)) goto lab3; /* among, line 49 */
            if (!(find_among(z, a_0, 8))) goto lab3;
            goto lab2;
        lab3:
            z->c = c2;
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab1;
                z->c = ret; /* next, line 49 */
            }
        }
    lab2:
        z->I[0] = z->c; /* setmark p1, line 50 */
        goto lab0;
    lab1:
        z->c = c1;
        if (out_grouping_U(z, g_v, 97, 369, 0)) return 0; /* non v, line 53 */
        {    /* gopast */ /* grouping v, line 53 */
            int ret = out_grouping_U(z, g_v, 97, 369, 1);
            if (ret < 0) return 0;
            z->c += ret;
        }
        z->I[0] = z->c; /* setmark p1, line 53 */
    }
lab0:
    return 1;
}