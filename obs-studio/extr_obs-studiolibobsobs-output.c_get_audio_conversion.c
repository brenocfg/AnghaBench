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
struct audio_convert_info {int dummy; } ;
struct obs_output {struct audio_convert_info audio_conversion; scalar_t__ audio_conversion_set; } ;

/* Variables and functions */

__attribute__((used)) static inline struct audio_convert_info *get_audio_conversion(
		struct obs_output *output)
{
	return output->audio_conversion_set ? &output->audio_conversion : NULL;
}