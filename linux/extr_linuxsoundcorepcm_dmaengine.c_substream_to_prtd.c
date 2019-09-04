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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct dmaengine_pcm_runtime_data {int dummy; } ;
struct TYPE_2__ {struct dmaengine_pcm_runtime_data* private_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct dmaengine_pcm_runtime_data *substream_to_prtd(
	const struct snd_pcm_substream *substream)
{
	return substream->runtime->private_data;
}