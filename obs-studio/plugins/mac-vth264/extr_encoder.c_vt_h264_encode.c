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
typedef  int /*<<< orphan*/  uint8_t ;
struct vt_h264_encoder {int /*<<< orphan*/  queue; int /*<<< orphan*/  session; int /*<<< orphan*/  fps_num; int /*<<< orphan*/  fps_den; } ;
struct encoder_packet {int dummy; } ;
struct encoder_frame {int pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/ * CVPixelBufferRef ;
typedef  int /*<<< orphan*/  CMTime ;
typedef  int /*<<< orphan*/ * CMSampleBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  CMSimpleQueueDequeue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMTimeMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMTimeMultiply (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CVPixelBufferGetBaseAddressOfPlane (int /*<<< orphan*/ *,int) ; 
 size_t CVPixelBufferGetBytesPerRowOfPlane (int /*<<< orphan*/ *,int) ; 
 size_t CVPixelBufferGetHeightOfPlane (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CVPixelBufferLockBaseAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferUnlockBaseAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int MAX_AV_PLANES ; 
 int /*<<< orphan*/  STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTCompressionSessionEncodeFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_BLOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_cached_pixel_buffer (struct vt_h264_encoder*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int parse_sample (struct vt_h264_encoder*,int /*<<< orphan*/ *,struct encoder_packet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vt_h264_encode(void *data, struct encoder_frame *frame,
			   struct encoder_packet *packet, bool *received_packet)
{
	struct vt_h264_encoder *enc = data;

	OSStatus code;

	CMTime dur = CMTimeMake(enc->fps_den, enc->fps_num);
	CMTime off = CMTimeMultiply(dur, 2);
	CMTime pts = CMTimeMultiply(dur, frame->pts);

	CVPixelBufferRef pixbuf = NULL;

	if (!get_cached_pixel_buffer(enc, &pixbuf)) {
		VT_BLOG(LOG_ERROR, "Unable to create pixel buffer");
		goto fail;
	}

	STATUS_CHECK(CVPixelBufferLockBaseAddress(pixbuf, 0));

	for (int i = 0; i < MAX_AV_PLANES; i++) {
		if (frame->data[i] == NULL)
			break;
		uint8_t *p = (uint8_t *)CVPixelBufferGetBaseAddressOfPlane(
			pixbuf, i);
		uint8_t *f = frame->data[i];
		size_t plane_linesize =
			CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
		size_t plane_height = CVPixelBufferGetHeightOfPlane(pixbuf, i);

		for (size_t j = 0; j < plane_height; j++) {
			memcpy(p, f, frame->linesize[i]);
			p += plane_linesize;
			f += frame->linesize[i];
		}
	}

	STATUS_CHECK(CVPixelBufferUnlockBaseAddress(pixbuf, 0));

	STATUS_CHECK(VTCompressionSessionEncodeFrame(enc->session, pixbuf, pts,
						     dur, NULL, pixbuf, NULL));

	CMSampleBufferRef buffer =
		(CMSampleBufferRef)CMSimpleQueueDequeue(enc->queue);

	// No samples waiting in the queue
	if (buffer == NULL)
		return true;

	*received_packet = true;
	return parse_sample(enc, buffer, packet, off);

fail:
	return false;
}