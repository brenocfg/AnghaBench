#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* array; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;
typedef  TYPE_2__ obs_script_t ;

/* Variables and functions */
 scalar_t__ ptr_valid (TYPE_2__ const*) ; 

const char *obs_script_get_description(const obs_script_t *script)
{
	return ptr_valid(script) ? script->desc.array : NULL;
}