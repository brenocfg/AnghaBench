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
struct atmel_runtime_data {int dummy; } ;
struct TYPE_2__ {struct atmel_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct atmel_runtime_data*) ; 

__attribute__((used)) static int atmel_pcm_close(struct snd_pcm_substream *substream)
{
	struct atmel_runtime_data *prtd = substream->runtime->private_data;

	kfree(prtd);
	return 0;
}