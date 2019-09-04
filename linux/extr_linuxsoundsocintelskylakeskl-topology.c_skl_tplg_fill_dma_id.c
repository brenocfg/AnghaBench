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
struct skl_pipe_params {int /*<<< orphan*/  format; int /*<<< orphan*/  stream; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  host_bps; int /*<<< orphan*/  host_dma_id; int /*<<< orphan*/  link_bps; int /*<<< orphan*/  link_index; int /*<<< orphan*/  link_dma_id; } ;
struct skl_pipe {TYPE_1__* p_params; scalar_t__ passthru; } ;
struct skl_module_cfg {int dev_type; struct skl_pipe* pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; int /*<<< orphan*/  stream; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  host_bps; int /*<<< orphan*/  host_dma_id; int /*<<< orphan*/  link_bps; int /*<<< orphan*/  link_index; int /*<<< orphan*/  link_dma_id; } ;

/* Variables and functions */
#define  SKL_DEVICE_HDAHOST 129 
#define  SKL_DEVICE_HDALINK 128 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct skl_pipe_params*,int) ; 

__attribute__((used)) static void skl_tplg_fill_dma_id(struct skl_module_cfg *mcfg,
				struct skl_pipe_params *params)
{
	struct skl_pipe *pipe = mcfg->pipe;

	if (pipe->passthru) {
		switch (mcfg->dev_type) {
		case SKL_DEVICE_HDALINK:
			pipe->p_params->link_dma_id = params->link_dma_id;
			pipe->p_params->link_index = params->link_index;
			pipe->p_params->link_bps = params->link_bps;
			break;

		case SKL_DEVICE_HDAHOST:
			pipe->p_params->host_dma_id = params->host_dma_id;
			pipe->p_params->host_bps = params->host_bps;
			break;

		default:
			break;
		}
		pipe->p_params->s_fmt = params->s_fmt;
		pipe->p_params->ch = params->ch;
		pipe->p_params->s_freq = params->s_freq;
		pipe->p_params->stream = params->stream;
		pipe->p_params->format = params->format;

	} else {
		memcpy(pipe->p_params, params, sizeof(*params));
	}
}