#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ ce; } ;
struct qm_portal {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa_touch_ro (scalar_t__) ; 

__attribute__((used)) static inline void qm_cl_touch_ro(struct qm_portal *p, u32 offset)
{
	dpaa_touch_ro(p->addr.ce + offset);
}