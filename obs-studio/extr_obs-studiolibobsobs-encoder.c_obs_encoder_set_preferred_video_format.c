#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {int preferred_format; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_encoder_t ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 

void obs_encoder_set_preferred_video_format(obs_encoder_t *encoder,
		enum video_format format)
{
	if (!encoder || encoder->info.type != OBS_ENCODER_VIDEO)
		return;

	encoder->preferred_format = format;
}