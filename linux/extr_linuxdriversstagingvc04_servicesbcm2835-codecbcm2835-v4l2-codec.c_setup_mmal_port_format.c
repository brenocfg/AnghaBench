#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  size; } ;
struct TYPE_13__ {int width; scalar_t__ y; scalar_t__ x; scalar_t__ height; } ;
struct TYPE_12__ {int den; scalar_t__ num; } ;
struct TYPE_14__ {int width; TYPE_5__ crop; TYPE_4__ frame_rate; scalar_t__ height; } ;
struct TYPE_15__ {TYPE_6__ video; } ;
struct TYPE_11__ {int /*<<< orphan*/  bitrate; int /*<<< orphan*/  encoding; } ;
struct vchiq_mmal_port {TYPE_8__ current_buffer; TYPE_7__ es; TYPE_3__ format; } ;
struct bcm2835_codec_q_data {int bytesperline; int crop_width; int /*<<< orphan*/  sizeimage; scalar_t__ crop_height; scalar_t__ height; TYPE_1__* fmt; } ;
struct bcm2835_codec_ctx {int /*<<< orphan*/  bitrate; TYPE_2__* dev; } ;
struct TYPE_10__ {scalar_t__ role; } ;
struct TYPE_9__ {int flags; int depth; int /*<<< orphan*/  mmal_fmt; } ;

/* Variables and functions */
 scalar_t__ DECODE ; 
 int V4L2_FMT_FLAG_COMPRESSED ; 

__attribute__((used)) static void setup_mmal_port_format(struct bcm2835_codec_ctx *ctx,
				   struct bcm2835_codec_q_data *q_data,
				   struct vchiq_mmal_port *port)
{
	port->format.encoding = q_data->fmt->mmal_fmt;

	if (!(q_data->fmt->flags & V4L2_FMT_FLAG_COMPRESSED)) {
		/* Raw image format - set width/height */
		port->es.video.width = (q_data->bytesperline << 3) /
						q_data->fmt->depth;
		port->es.video.height = q_data->height;
		port->es.video.crop.width = q_data->crop_width;
		port->es.video.crop.height = q_data->crop_height;
		port->es.video.frame_rate.num = 0;
		port->es.video.frame_rate.den = 1;
	} else {
		/* Compressed format - leave resolution as 0 for decode */
		if (ctx->dev->role == DECODE) {
			port->es.video.width = 0;
			port->es.video.height = 0;
			port->es.video.crop.width = 0;
			port->es.video.crop.height = 0;
		} else {
			port->es.video.width = q_data->crop_width;
			port->es.video.height = q_data->height;
			port->es.video.crop.width = q_data->crop_width;
			port->es.video.crop.height = q_data->crop_height;
			port->format.bitrate = ctx->bitrate;
		}
		port->es.video.frame_rate.num = 0;
		port->es.video.frame_rate.den = 1;
	}
	port->es.video.crop.x = 0;
	port->es.video.crop.y = 0;

	port->current_buffer.size = q_data->sizeimage;
}