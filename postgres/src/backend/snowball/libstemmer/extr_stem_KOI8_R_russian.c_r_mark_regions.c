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
 int in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $pV = <integer expression>, line 61 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 62 */
    {   int c1 = z->c; /* do, line 63 */
        {    /* gopast */ /* grouping v, line 64 */
            int ret = out_grouping(z, g_v, 192, 220, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[0] = z->c; /* setmark pV, line 64 */
        {    /* gopast */ /* non v, line 64 */
            int ret = in_grouping(z, g_v, 192, 220, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        {    /* gopast */ /* grouping v, line 65 */
            int ret = out_grouping(z, g_v, 192, 220, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 65 */
            int ret = in_grouping(z, g_v, 192, 220, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p2, line 65 */
    lab0:
        z->c = c1;
    }
    return 1;
}