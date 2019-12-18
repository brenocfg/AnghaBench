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
struct SN_env {int* I; int l; int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $pV = <integer expression>, line 30 */
    z->I[1] = z->l; /* $p1 = <integer expression>, line 31 */
    z->I[2] = z->l; /* $p2 = <integer expression>, line 32 */
    {   int c1 = z->c; /* do, line 34 */
        {    /* gopast */ /* grouping v, line 35 */
            int ret = out_grouping_U(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[0] = z->c; /* setmark pV, line 35 */
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 37 */
        {    /* gopast */ /* grouping v, line 38 */
            int ret = out_grouping_U(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab1;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 38 */
            int ret = in_grouping_U(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab1;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p1, line 38 */
        {    /* gopast */ /* grouping v, line 39 */
            int ret = out_grouping_U(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab1;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 39 */
            int ret = in_grouping_U(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab1;
            z->c += ret;
        }
        z->I[2] = z->c; /* setmark p2, line 39 */
    lab1:
        z->c = c2;
    }
    return 1;
}