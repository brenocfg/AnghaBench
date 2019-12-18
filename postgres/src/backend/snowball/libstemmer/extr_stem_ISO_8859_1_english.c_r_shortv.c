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
struct SN_env {int l; int c; scalar_t__ lb; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int /*<<< orphan*/  g_v_WXY ; 
 scalar_t__ in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ out_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_shortv(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 51 */
        if (out_grouping_b(z, g_v_WXY, 89, 121, 0)) goto lab1; /* non v_WXY, line 50 */
        if (in_grouping_b(z, g_v, 97, 121, 0)) goto lab1; /* grouping v, line 50 */
        if (out_grouping_b(z, g_v, 97, 121, 0)) goto lab1; /* non v, line 50 */
        goto lab0;
    lab1:
        z->c = z->l - m1;
        if (out_grouping_b(z, g_v, 97, 121, 0)) return 0; /* non v, line 52 */
        if (in_grouping_b(z, g_v, 97, 121, 0)) return 0; /* grouping v, line 52 */
        if (z->c > z->lb) return 0; /* atlimit, line 52 */
    }
lab0:
    return 1;
}