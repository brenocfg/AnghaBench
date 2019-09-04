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
struct obs_source_info {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {size_t num; struct obs_source_info* array; } ;
struct TYPE_4__ {TYPE_1__ source_types; } ;

/* Variables and functions */
 TYPE_2__* obs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct obs_source_info *get_source_info(const char *id)
{
	for (size_t i = 0; i < obs->source_types.num; i++) {
		struct obs_source_info *info = &obs->source_types.array[i];
		if (strcmp(info->id, id) == 0)
			return info;
	}

	return NULL;
}