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
 int VIDEO_FORMAT_NONE ; 

enum video_format obs_encoder_get_preferred_video_format(
		const obs_encoder_t *encoder)
{
	if (!encoder || encoder->info.type != OBS_ENCODER_VIDEO)
		return VIDEO_FORMAT_NONE;

	return encoder->preferred_format;
}