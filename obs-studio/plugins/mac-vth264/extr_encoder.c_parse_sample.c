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
struct TYPE_4__ {int /*<<< orphan*/  num; int /*<<< orphan*/  array; int /*<<< orphan*/  da; } ;
struct darray {int dummy; } ;
struct TYPE_3__ {scalar_t__ num; struct darray da; } ;
struct vt_h264_encoder {int fps_den; TYPE_2__ packet_data; TYPE_1__ extra_data; scalar_t__ bframes; scalar_t__ fps_num; } ;
struct encoder_packet {int keyframe; int /*<<< orphan*/  size; int /*<<< orphan*/  data; void* dts; void* pts; int /*<<< orphan*/  type; } ;
typedef  void* int64_t ;
typedef  int Float64 ;
typedef  int /*<<< orphan*/  CMTime ;
typedef  int /*<<< orphan*/  CMSampleBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMSampleBufferGetDecodeTimeStamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMSampleBufferGetPresentationTimeStamp (int /*<<< orphan*/ ) ; 
 scalar_t__ CMTimeGetSeconds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMTimeMultiplyByFloat64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMTimeSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  convert_sample_to_annexb (struct vt_h264_encoder*,int /*<<< orphan*/ *,struct darray*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  da_resize (TYPE_2__,int /*<<< orphan*/ ) ; 
 int is_sample_keyframe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool parse_sample(struct vt_h264_encoder *enc, CMSampleBufferRef buffer,
			 struct encoder_packet *packet, CMTime off)
{
	CMTime pts = CMSampleBufferGetPresentationTimeStamp(buffer);
	CMTime dts = CMSampleBufferGetDecodeTimeStamp(buffer);

	pts = CMTimeMultiplyByFloat64(pts,
				      ((Float64)enc->fps_num / enc->fps_den));
	dts = CMTimeMultiplyByFloat64(dts,
				      ((Float64)enc->fps_num / enc->fps_den));

	// imitate x264's negative dts when bframes might have pts < dts
	if (enc->bframes)
		dts = CMTimeSubtract(dts, off);

	bool keyframe = is_sample_keyframe(buffer);

	da_resize(enc->packet_data, 0);

	// If we are still looking for extra data
	struct darray *extra_data = NULL;
	if (enc->extra_data.num == 0)
		extra_data = &enc->extra_data.da;

	if (!convert_sample_to_annexb(enc, &enc->packet_data.da, extra_data,
				      buffer, keyframe))
		goto fail;

	packet->type = OBS_ENCODER_VIDEO;
	packet->pts = (int64_t)(CMTimeGetSeconds(pts));
	packet->dts = (int64_t)(CMTimeGetSeconds(dts));
	packet->data = enc->packet_data.array;
	packet->size = enc->packet_data.num;
	packet->keyframe = keyframe;

	CFRelease(buffer);
	return true;

fail:
	CFRelease(buffer);
	return false;
}