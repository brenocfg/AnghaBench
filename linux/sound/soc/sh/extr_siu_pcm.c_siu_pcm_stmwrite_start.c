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
struct siu_stream {int /*<<< orphan*/  tasklet; scalar_t__ rw_flg; scalar_t__ cur_period; } ;
struct siu_port {struct siu_stream playback; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ RWF_STM_WT ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int siu_pcm_stmwrite_start(struct siu_port *port_info)
{
	struct siu_stream *siu_stream = &port_info->playback;

	if (siu_stream->rw_flg)
		return -EPERM;

	/* Current period in buffer */
	port_info->playback.cur_period = 0;

	/* during stmwrite flag set */
	siu_stream->rw_flg = RWF_STM_WT;

	/* DMA transfer start */
	tasklet_schedule(&siu_stream->tasklet);

	return 0;
}