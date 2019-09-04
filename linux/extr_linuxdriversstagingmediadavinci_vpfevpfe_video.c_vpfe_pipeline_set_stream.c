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
struct vpfe_pipeline {int dummy; } ;
typedef  enum vpfe_pipeline_stream_state { ____Placeholder_vpfe_pipeline_stream_state } vpfe_pipeline_stream_state ;

/* Variables and functions */
 int VPFE_PIPELINE_STREAM_STOPPED ; 
 int vpfe_pipeline_disable (struct vpfe_pipeline*) ; 
 int vpfe_pipeline_enable (struct vpfe_pipeline*) ; 

__attribute__((used)) static int vpfe_pipeline_set_stream(struct vpfe_pipeline *pipe,
			    enum vpfe_pipeline_stream_state state)
{
	if (state == VPFE_PIPELINE_STREAM_STOPPED)
		return vpfe_pipeline_disable(pipe);

	return vpfe_pipeline_enable(pipe);
}