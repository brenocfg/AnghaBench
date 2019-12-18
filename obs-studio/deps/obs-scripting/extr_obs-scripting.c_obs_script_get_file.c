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
struct TYPE_5__ {char* array; } ;
struct TYPE_6__ {TYPE_1__ file; } ;
typedef  TYPE_2__ obs_script_t ;

/* Variables and functions */
 scalar_t__ ptr_valid (TYPE_2__ const*) ; 

const char *obs_script_get_file(const obs_script_t *script)
{
	const char *file = ptr_valid(script) ? script->file.array : "";
	return file ? file : "";
}