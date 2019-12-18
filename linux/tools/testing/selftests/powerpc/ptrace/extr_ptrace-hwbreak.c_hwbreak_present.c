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
struct TYPE_2__ {scalar_t__ num_data_bps; } ;

/* Variables and functions */
 TYPE_1__ dbginfo ; 

__attribute__((used)) static bool hwbreak_present(void)
{
	return (dbginfo.num_data_bps != 0);
}