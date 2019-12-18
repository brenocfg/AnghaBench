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
struct ssi_priv {scalar_t__ inuse; } ;
struct snd_soc_dai {size_t id; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct ssi_priv* ssi_cpu_data ; 

__attribute__((used)) static void ssi_shutdown(struct snd_pcm_substream *substream,
			 struct snd_soc_dai *dai)
{
	struct ssi_priv *ssi = &ssi_cpu_data[dai->id];

	ssi->inuse = 0;
}