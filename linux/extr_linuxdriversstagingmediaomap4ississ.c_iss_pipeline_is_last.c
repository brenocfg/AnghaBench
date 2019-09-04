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
struct media_pad {struct media_entity* entity; } ;
struct media_entity {int /*<<< orphan*/  pipe; } ;
struct iss_pipeline {scalar_t__ stream_state; TYPE_1__* output; } ;
struct TYPE_2__ {int /*<<< orphan*/  pad; } ;

/* Variables and functions */
 scalar_t__ ISS_PIPELINE_STREAM_STOPPED ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct iss_pipeline* to_iss_pipeline (struct media_entity*) ; 

__attribute__((used)) static int iss_pipeline_is_last(struct media_entity *me)
{
	struct iss_pipeline *pipe;
	struct media_pad *pad;

	if (!me->pipe)
		return 0;
	pipe = to_iss_pipeline(me);
	if (pipe->stream_state == ISS_PIPELINE_STREAM_STOPPED)
		return 0;
	pad = media_entity_remote_pad(&pipe->output->pad);
	return pad->entity == me;
}