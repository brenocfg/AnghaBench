#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct my_timming {int dummy; } ;
struct maven_data {TYPE_2__* primary_head; } ;
struct TYPE_3__ {int /*<<< orphan*/  maven; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int maven_compute_timming (void*,struct my_timming*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int maven_out_compute(void* md, struct my_timming* mt) {
#define mdinfo ((struct maven_data*)md)
#define minfo (mdinfo->primary_head)
	return maven_compute_timming(md, mt, &minfo->hw.maven);
#undef minfo
#undef mdinfo
}