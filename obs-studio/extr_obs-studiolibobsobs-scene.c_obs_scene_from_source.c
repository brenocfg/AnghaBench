#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_scene_t ;
struct TYPE_9__ {scalar_t__ id; } ;

/* Variables and functions */
 TYPE_4__ scene_info ; 

obs_scene_t *obs_scene_from_source(const obs_source_t *source)
{
	if (!source || source->info.id != scene_info.id)
		return NULL;

	return source->context.data;
}