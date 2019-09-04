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
struct azx_dev {int dummy; } ;
struct TYPE_2__ {struct azx_dev* private_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct azx_dev *get_azx_dev(struct snd_pcm_substream *substream)
{
	return substream->runtime->private_data;
}