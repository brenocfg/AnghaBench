#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float balance; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 scalar_t__ obs_source_valid (TYPE_1__ const*,char*) ; 

float obs_source_get_balance_value(const obs_source_t *source)
{
	return obs_source_valid(source, "obs_source_get_balance_value")
		       ? source->balance
		       : 0.5f;
}