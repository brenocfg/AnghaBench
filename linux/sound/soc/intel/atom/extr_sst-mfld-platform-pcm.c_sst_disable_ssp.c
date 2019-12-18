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
struct snd_soc_dai {int /*<<< orphan*/  name; int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  send_ssp_cmd (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_handle_vb_timer (struct snd_soc_dai*,int) ; 

__attribute__((used)) static void sst_disable_ssp(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	if (!dai->active) {
		send_ssp_cmd(dai, dai->name, 0);
		sst_handle_vb_timer(dai, false);
	}
}