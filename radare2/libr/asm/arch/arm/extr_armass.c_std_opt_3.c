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
struct TYPE_3__ {int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ ArmOpcode ;

/* Variables and functions */

__attribute__((used)) static void std_opt_3(ArmOpcode *ao) {
	ao->a[3] = ao->a[2];
	ao->a[2] = ao->a[1];
	ao->a[1] = ao->a[0];
}