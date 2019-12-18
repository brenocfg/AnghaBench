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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int AC_WCAP_OUT_AMP ; 
 int get_wcaps (struct hdac_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_codec_write (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdac_hdmi_set_amp(struct hdac_device *hdev,
				   hda_nid_t nid, int val)
{
	if (get_wcaps(hdev, nid) & AC_WCAP_OUT_AMP)
		snd_hdac_codec_write(hdev, nid, 0,
					AC_VERB_SET_AMP_GAIN_MUTE, val);
}