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
 int /*<<< orphan*/  g_V1 ; 
 int in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $p1 = <integer expression>, line 44 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 45 */
    if (out_grouping(z, g_V1, 97, 246, 1) < 0) return 0; /* goto */ /* grouping V1, line 47 */
    {    /* gopast */ /* non V1, line 47 */
        int ret = in_grouping(z, g_V1, 97, 246, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[0] = z->c; /* setmark p1, line 47 */
    if (out_grouping(z, g_V1, 97, 246, 1) < 0) return 0; /* goto */ /* grouping V1, line 48 */
    {    /* gopast */ /* non V1, line 48 */
        int ret = in_grouping(z, g_V1, 97, 246, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[1] = z->c; /* setmark p2, line 48 */
    return 1;
}