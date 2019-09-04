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
struct snd_pcm_substream {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  ppcap; } ;

/* Variables and functions */
 struct hdac_bus* get_bus_ctx (struct snd_pcm_substream*) ; 
 int skl_coupled_trigger (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int skl_platform_pcm_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	struct hdac_bus *bus = get_bus_ctx(substream);

	if (!bus->ppcap)
		return skl_coupled_trigger(substream, cmd);

	return 0;
}