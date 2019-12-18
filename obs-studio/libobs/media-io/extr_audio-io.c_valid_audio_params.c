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
struct audio_output_info {scalar_t__ samples_per_sec; scalar_t__ speakers; scalar_t__ name; scalar_t__ format; } ;

/* Variables and functions */

__attribute__((used)) static inline bool valid_audio_params(const struct audio_output_info *info)
{
	return info->format && info->name && info->samples_per_sec > 0 &&
	       info->speakers > 0;
}