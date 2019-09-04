#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t last; int sign; int /*<<< orphan*/ * dgts; } ;
typedef  TYPE_1__ RNumBig ;

/* Variables and functions */

__attribute__((used)) static inline void r_big_zero(RNumBig *n) {
	while ((n->last>0) && !n->dgts[n->last])
		n->last--;
        if (!n->last && !*n->dgts)
		n->sign = 1; /* hack to avoid -0 */
}