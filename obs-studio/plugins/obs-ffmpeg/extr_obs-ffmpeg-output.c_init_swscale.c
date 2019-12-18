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
struct TYPE_4__ {int /*<<< orphan*/  scale_height; int /*<<< orphan*/  scale_width; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ffmpeg_data {int /*<<< orphan*/  swscale; TYPE_1__ config; } ;
struct TYPE_5__ {int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SWS_BICUBIC ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,struct ffmpeg_data*,char*) ; 
 int /*<<< orphan*/  sws_getContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_swscale(struct ffmpeg_data *data, AVCodecContext *context)
{
	data->swscale = sws_getContext(
		data->config.width, data->config.height, data->config.format,
		data->config.scale_width, data->config.scale_height,
		context->pix_fmt, SWS_BICUBIC, NULL, NULL, NULL);

	if (!data->swscale) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Could not initialize swscale");
		return false;
	}

	return true;
}