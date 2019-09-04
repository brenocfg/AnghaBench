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
struct siu_stream {int xfer_cnt; int /*<<< orphan*/  tasklet; scalar_t__ rw_flg; scalar_t__ cur_period; } ;
struct siu_port {struct siu_stream capture; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ RWF_STM_RD ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int siu_pcm_stmread_start(struct siu_port *port_info)
{
	struct siu_stream *siu_stream = &port_info->capture;

	if (siu_stream->xfer_cnt > 0x1000000)
		return -EINVAL;
	if (siu_stream->rw_flg)
		return -EPERM;

	/* Current period in buffer */
	siu_stream->cur_period = 0;

	/* during stmread flag set */
	siu_stream->rw_flg = RWF_STM_RD;

	tasklet_schedule(&siu_stream->tasklet);

	return 0;
}