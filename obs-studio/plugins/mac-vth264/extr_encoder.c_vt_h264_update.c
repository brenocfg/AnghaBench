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
typedef  scalar_t__ uint32_t ;
struct vt_h264_encoder {scalar_t__ bitrate; int limit_bitrate; int /*<<< orphan*/  session; int /*<<< orphan*/  rc_max_bitrate_window; int /*<<< orphan*/  rc_max_bitrate; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  CFNumberRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFNumberGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  VTSessionCopyProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_BLOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dump_encoder_info (struct vt_h264_encoder*) ; 
 int /*<<< orphan*/  kCFNumberIntType ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_AverageBitRate ; 
 scalar_t__ noErr ; 
 scalar_t__ session_set_bitrate (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_params (struct vt_h264_encoder*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vt_h264_update(void *data, obs_data_t *settings)
{
	struct vt_h264_encoder *enc = data;

	uint32_t old_bitrate = enc->bitrate;
	bool old_limit_bitrate = enc->limit_bitrate;

	update_params(enc, settings);

	if (old_bitrate == enc->bitrate &&
	    old_limit_bitrate == enc->limit_bitrate)
		return true;

	OSStatus code = session_set_bitrate(enc->session, enc->bitrate,
					    enc->limit_bitrate,
					    enc->rc_max_bitrate,
					    enc->rc_max_bitrate_window);
	if (code != noErr)
		VT_BLOG(LOG_WARNING, "failed to set bitrate to session");

	CFNumberRef n;
	VTSessionCopyProperty(enc->session,
			      kVTCompressionPropertyKey_AverageBitRate, NULL,
			      &n);

	uint32_t session_bitrate;
	CFNumberGetValue(n, kCFNumberIntType, &session_bitrate);
	CFRelease(n);

	if (session_bitrate == old_bitrate) {
		VT_BLOG(LOG_WARNING,
			"failed to update current session "
			" bitrate from %d->%d",
			old_bitrate, enc->bitrate);
	}

	dump_encoder_info(enc);
	return true;
}