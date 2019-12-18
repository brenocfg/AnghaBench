#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* insns; } ;
struct TYPE_5__ {void* insns; TYPE_1__ ptr; } ;
struct TYPE_6__ {TYPE_2__ u; scalar_t__ fill_helper; } ;

/* Variables and functions */
 TYPE_3__* tests ; 

__attribute__((used)) static void *filter_pointer(int which)
{
	if (tests[which].fill_helper)
		return tests[which].u.ptr.insns;
	else
		return tests[which].u.insns;
}