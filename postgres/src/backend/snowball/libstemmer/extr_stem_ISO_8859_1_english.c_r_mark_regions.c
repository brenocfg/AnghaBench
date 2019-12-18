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
 int in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $p1 = <integer expression>, line 33 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 34 */
    {   int c1 = z->c; /* do, line 35 */
        {   int c2 = z->c; /* or, line 41 */
            if (z->c + 4 >= z->l || z->p[z->c + 4] >> 5 != 3 || !((2375680 >> (z->p[z->c + 4] & 0x1f)) & 1)) goto lab2; /* among, line 36 */
            if (!(find_among(z, a_0, 3))) goto lab2;
            goto lab1;
        lab2:
            z->c = c2;
            {    /* gopast */ /* grouping v, line 41 */
                int ret = out_grouping(z, g_v, 97, 121, 1);
                if (ret < 0) goto lab0;
                z->c += ret;
            }
            {    /* gopast */ /* non v, line 41 */
                int ret = in_grouping(z, g_v, 97, 121, 1);
                if (ret < 0) goto lab0;
                z->c += ret;
            }
        }
    lab1:
        z->I[0] = z->c; /* setmark p1, line 42 */
        {    /* gopast */ /* grouping v, line 43 */
            int ret = out_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 43 */
            int ret = in_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p2, line 43 */
    lab0:
        z->c = c1;
    }
    return 1;
}