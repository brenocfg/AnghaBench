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
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int (* get_dropped_frames ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_valid (TYPE_3__ const*,char*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int obs_output_get_frames_dropped(const obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_get_frames_dropped"))
		return 0;
	if (!output->info.get_dropped_frames)
		return 0;

	return output->info.get_dropped_frames(output->context.data);
}