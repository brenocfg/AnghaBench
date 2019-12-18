#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_scale_info {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  format; } ;
struct video_output_info {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  format; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_video_info ) (int /*<<< orphan*/ ,struct video_scale_info*) ;} ;
struct obs_encoder {TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  media; } ;

/* Variables and functions */
 scalar_t__ obs_encoder_get_height (struct obs_encoder*) ; 
 scalar_t__ obs_encoder_get_width (struct obs_encoder*) ; 
 int /*<<< orphan*/  obs_encoder_set_scaled_size (struct obs_encoder*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct video_scale_info*) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void get_video_info(struct obs_encoder *encoder,
				  struct video_scale_info *info)
{
	const struct video_output_info *voi;
	voi = video_output_get_info(encoder->media);

	info->format = voi->format;
	info->colorspace = voi->colorspace;
	info->range = voi->range;
	info->width = obs_encoder_get_width(encoder);
	info->height = obs_encoder_get_height(encoder);

	if (encoder->info.get_video_info)
		encoder->info.get_video_info(encoder->context.data, info);

	if (info->width != voi->width || info->height != voi->height)
		obs_encoder_set_scaled_size(encoder, info->width, info->height);
}