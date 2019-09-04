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
struct mp_csp_col_xy {int x; int y; } ;

/* Variables and functions */

__attribute__((used)) static inline float mp_xy_Z(struct mp_csp_col_xy xy) {
    return (1 - xy.x - xy.y) / xy.y;
}