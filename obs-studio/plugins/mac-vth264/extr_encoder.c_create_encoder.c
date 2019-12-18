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
struct vt_h264_encoder {int hw_enc; float keyint; float fps_den; int /*<<< orphan*/  session; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  rc_max_bitrate_window; int /*<<< orphan*/  rc_max_bitrate; int /*<<< orphan*/  limit_bitrate; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  profile; scalar_t__ bframes; scalar_t__ fps_num; int /*<<< orphan*/  queue; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  vt_encoder_id; } ;
typedef  int /*<<< orphan*/  VTCompressionSessionRef ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFDictionaryRef ;
typedef  int /*<<< orphan*/ * CFBooleanRef ;

/* Variables and functions */
 int CFBooleanGetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  STATUS_CHECK (scalar_t__) ; 
 scalar_t__ VTCompressionSessionCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ VTCompressionSessionPrepareToEncodeFrames (int /*<<< orphan*/ ) ; 
 scalar_t__ VTSessionCopyProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VT_BLOG (int /*<<< orphan*/ ,char*) ; 
 float ceil (float) ; 
 int /*<<< orphan*/ * create_encoder_spec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_pixbuf_spec (struct vt_h264_encoder*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBooleanFalse ; 
 int /*<<< orphan*/  kCFBooleanTrue ; 
 int /*<<< orphan*/  kCMVideoCodecType_H264 ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_AllowFrameReordering ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_ExpectedFrameRate ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_MaxKeyFrameInterval ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_ProfileLevel ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_RealTime ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder ; 
 int /*<<< orphan*/  log_osstatus (int /*<<< orphan*/ ,struct vt_h264_encoder*,char*,scalar_t__) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  obs_to_vt_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_encoded_callback ; 
 scalar_t__ session_set_bitrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ session_set_colorspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ session_set_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ session_set_prop_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static bool create_encoder(struct vt_h264_encoder *enc)
{
	OSStatus code;

	VTCompressionSessionRef s;

	CFDictionaryRef encoder_spec = create_encoder_spec(enc->vt_encoder_id);
	CFDictionaryRef pixbuf_spec = create_pixbuf_spec(enc);

	STATUS_CHECK(VTCompressionSessionCreate(
		kCFAllocatorDefault, enc->width, enc->height,
		kCMVideoCodecType_H264, encoder_spec, pixbuf_spec, NULL,
		&sample_encoded_callback, enc->queue, &s));

	CFRelease(encoder_spec);
	CFRelease(pixbuf_spec);

	CFBooleanRef b = NULL;
	code = VTSessionCopyProperty(
		s,
		kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder,
		NULL, &b);

	if (code == noErr && (enc->hw_enc = CFBooleanGetValue(b)))
		VT_BLOG(LOG_INFO, "session created with hardware encoding");
	else
		enc->hw_enc = false;

	if (b != NULL)
		CFRelease(b);

	STATUS_CHECK(session_set_prop_int(
		s, kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration,
		enc->keyint));
	STATUS_CHECK(session_set_prop_int(
		s, kVTCompressionPropertyKey_MaxKeyFrameInterval,
		enc->keyint * ((float)enc->fps_num / enc->fps_den)));
	STATUS_CHECK(session_set_prop_int(
		s, kVTCompressionPropertyKey_ExpectedFrameRate,
		ceil((float)enc->fps_num / enc->fps_den)));
	STATUS_CHECK(session_set_prop(
		s, kVTCompressionPropertyKey_AllowFrameReordering,
		enc->bframes ? kCFBooleanTrue : kCFBooleanFalse));

	// This can fail depending on hardware configuration
	code = session_set_prop(s, kVTCompressionPropertyKey_RealTime,
				kCFBooleanTrue);
	if (code != noErr)
		log_osstatus(LOG_WARNING, enc,
			     "setting "
			     "kVTCompressionPropertyKey_RealTime, "
			     "frame delay might be increased",
			     code);

	STATUS_CHECK(session_set_prop(s, kVTCompressionPropertyKey_ProfileLevel,
				      obs_to_vt_profile(enc->profile)));

	STATUS_CHECK(session_set_bitrate(s, enc->bitrate, enc->limit_bitrate,
					 enc->rc_max_bitrate,
					 enc->rc_max_bitrate_window));

	STATUS_CHECK(session_set_colorspace(s, enc->colorspace));

	STATUS_CHECK(VTCompressionSessionPrepareToEncodeFrames(s));

	enc->session = s;

	return true;

fail:
	if (encoder_spec != NULL)
		CFRelease(encoder_spec);
	if (pixbuf_spec != NULL)
		CFRelease(pixbuf_spec);

	return false;
}