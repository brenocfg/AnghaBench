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
struct SN_env {scalar_t__* I; scalar_t__ c; } ;

/* Variables and functions */

__attribute__((used)) static int r_R2(struct SN_env * z) { /* backwardmode */
    if (!(z->I[2] <= z->c)) return 0; /* $(<integer expression> <= <integer expression>), line 65 */
    return 1;
}