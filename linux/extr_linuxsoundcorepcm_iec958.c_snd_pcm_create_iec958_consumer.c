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
typedef  int /*<<< orphan*/  u8 ;
struct snd_pcm_runtime {int /*<<< orphan*/  format; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int create_iec958_consumer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 

int snd_pcm_create_iec958_consumer(struct snd_pcm_runtime *runtime, u8 *cs,
	size_t len)
{
	return create_iec958_consumer(runtime->rate,
				      snd_pcm_format_width(runtime->format),
				      cs, len);
}