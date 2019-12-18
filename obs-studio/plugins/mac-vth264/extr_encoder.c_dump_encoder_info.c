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
struct vt_h264_encoder {char* profile; scalar_t__ hw_enc; int /*<<< orphan*/  rc_max_bitrate_window; int /*<<< orphan*/  rc_max_bitrate; scalar_t__ limit_bitrate; int /*<<< orphan*/  keyint; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fps_den; int /*<<< orphan*/  fps_num; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  vt_encoder_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  VT_BLOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void dump_encoder_info(struct vt_h264_encoder *enc)
{
	VT_BLOG(LOG_INFO,
		"settings:\n"
		"\tvt_encoder_id          %s\n"
		"\tbitrate:               %d (kbps)\n"
		"\tfps_num:               %d\n"
		"\tfps_den:               %d\n"
		"\twidth:                 %d\n"
		"\theight:                %d\n"
		"\tkeyint:                %d (s)\n"
		"\tlimit_bitrate:         %s\n"
		"\trc_max_bitrate:        %d (kbps)\n"
		"\trc_max_bitrate_window: %f (s)\n"
		"\thw_enc:                %s\n"
		"\tprofile:               %s\n",
		enc->vt_encoder_id, enc->bitrate, enc->fps_num, enc->fps_den,
		enc->width, enc->height, enc->keyint,
		enc->limit_bitrate ? "on" : "off", enc->rc_max_bitrate,
		enc->rc_max_bitrate_window, enc->hw_enc ? "on" : "off",
		(enc->profile != NULL && !!strlen(enc->profile)) ? enc->profile
								 : "default");
}