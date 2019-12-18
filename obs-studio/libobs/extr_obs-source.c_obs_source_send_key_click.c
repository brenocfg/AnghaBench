#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct obs_key_event {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int output_flags; int /*<<< orphan*/  (* key_click ) (int /*<<< orphan*/ ,struct obs_key_event const*,int) ;} ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_INTERACTION ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct obs_key_event const*,int) ; 

void obs_source_send_key_click(obs_source_t *source,
			       const struct obs_key_event *event, bool key_up)
{
	if (!obs_source_valid(source, "obs_source_send_key_click"))
		return;

	if (source->info.output_flags & OBS_SOURCE_INTERACTION) {
		if (source->info.key_click) {
			source->info.key_click(source->context.data, event,
					       key_up);
		}
	}
}