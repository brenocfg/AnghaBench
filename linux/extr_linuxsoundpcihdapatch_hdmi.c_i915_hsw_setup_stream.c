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
typedef  int /*<<< orphan*/  u32 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  haswell_verify_D0 (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdmi_setup_stream (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i915_hsw_setup_stream(struct hda_codec *codec, hda_nid_t cvt_nid,
				 hda_nid_t pin_nid, u32 stream_tag, int format)
{
	haswell_verify_D0(codec, cvt_nid, pin_nid);
	return hdmi_setup_stream(codec, cvt_nid, pin_nid, stream_tag, format);
}