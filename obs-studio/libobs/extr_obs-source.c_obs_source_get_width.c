#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 scalar_t__ OBS_SOURCE_TYPE_FILTER ; 
 int /*<<< orphan*/  data_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  get_base_width (TYPE_2__*) ; 
 int /*<<< orphan*/  get_recurse_width (TYPE_2__*) ; 

uint32_t obs_source_get_width(obs_source_t *source)
{
	if (!data_valid(source, "obs_source_get_width"))
		return 0;

	return (source->info.type != OBS_SOURCE_TYPE_FILTER)
		       ? get_recurse_width(source)
		       : get_base_width(source);
}