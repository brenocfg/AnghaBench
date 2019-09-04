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
struct pm_qos_constraints {int /*<<< orphan*/  target_value; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static inline void pm_qos_set_value(struct pm_qos_constraints *c, s32 value)
{
	c->target_value = value;
}