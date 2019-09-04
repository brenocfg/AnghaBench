#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iss_pipeline {int stream_state; } ;
typedef  enum iss_pipeline_stream_state { ____Placeholder_iss_pipeline_stream_state } iss_pipeline_stream_state ;

/* Variables and functions */
 int ISS_PIPELINE_STREAM_STOPPED ; 
 int iss_pipeline_disable (struct iss_pipeline*,int /*<<< orphan*/ *) ; 
 int iss_pipeline_enable (struct iss_pipeline*,int) ; 

int omap4iss_pipeline_set_stream(struct iss_pipeline *pipe,
				 enum iss_pipeline_stream_state state)
{
	int ret;

	if (state == ISS_PIPELINE_STREAM_STOPPED)
		ret = iss_pipeline_disable(pipe, NULL);
	else
		ret = iss_pipeline_enable(pipe, state);

	if (ret == 0 || state == ISS_PIPELINE_STREAM_STOPPED)
		pipe->stream_state = state;

	return ret;
}