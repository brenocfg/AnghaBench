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
struct ipc_dsp_hdr {int cmd_id; int mod_index_id; int pipe_id; int length; scalar_t__ mod_id; } ;

/* Variables and functions */

void sst_fill_header_dsp(struct ipc_dsp_hdr *dsp, int msg,
					int pipe_id, int len)
{
	dsp->cmd_id = msg;
	dsp->mod_index_id = 0xff;
	dsp->pipe_id = pipe_id;
	dsp->length = len;
	dsp->mod_id = 0;
}