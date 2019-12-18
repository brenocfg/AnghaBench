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
    z->I[0] = z->l; /* $p1 = <integer expression>, line 66 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 67 */
    {    /* gopast */ /* grouping v, line 69 */
        int ret = out_grouping_U(z, g_v, 97, 232, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    {    /* gopast */ /* non v, line 69 */
        int ret = in_grouping_U(z, g_v, 97, 232, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[0] = z->c; /* setmark p1, line 69 */
    /* try, line 70 */
    if (!(z->I[0] < 3)) goto lab0; /* $(<integer expression> < <integer expression>), line 70 */
    z->I[0] = 3; /* $p1 = <integer expression>, line 70 */
lab0:
    {    /* gopast */ /* grouping v, line 71 */
        int ret = out_grouping_U(z, g_v, 97, 232, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    {    /* gopast */ /* non v, line 71 */
        int ret = in_grouping_U(z, g_v, 97, 232, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[1] = z->c; /* setmark p2, line 71 */
    return 1;
}