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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int sst_send_pipe_gains (struct snd_soc_dai*,int,int) ; 

__attribute__((used)) static int sst_media_digital_mute(struct snd_soc_dai *dai, int mute, int stream)
{

	return sst_send_pipe_gains(dai, stream, mute);
}