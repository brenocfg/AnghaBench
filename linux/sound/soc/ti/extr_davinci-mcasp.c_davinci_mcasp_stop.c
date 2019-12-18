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
struct davinci_mcasp {int /*<<< orphan*/  streams; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  mcasp_stop_rx (struct davinci_mcasp*) ; 
 int /*<<< orphan*/  mcasp_stop_tx (struct davinci_mcasp*) ; 

__attribute__((used)) static void davinci_mcasp_stop(struct davinci_mcasp *mcasp, int stream)
{
	mcasp->streams--;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		mcasp_stop_tx(mcasp);
	else
		mcasp_stop_rx(mcasp);
}