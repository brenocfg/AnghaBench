#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdac_hdmi_priv {TYPE_1__* drv_data; } ;
struct hdac_device {int dummy; } ;
struct TYPE_2__ {unsigned int vendor_nid; } ;

/* Variables and functions */
 unsigned int INTEL_EN_DP12 ; 
 int /*<<< orphan*/  INTEL_GET_VENDOR_VERB ; 
 int /*<<< orphan*/  INTEL_SET_VENDOR_VERB ; 
 struct hdac_hdmi_priv* hdev_to_hdmi_priv (struct hdac_device*) ; 
 unsigned int snd_hdac_codec_read (struct hdac_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hdac_hdmi_skl_enable_dp12(struct hdac_device *hdev)
{
	unsigned int vendor_param;
	struct hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	unsigned int vendor_nid = hdmi->drv_data->vendor_nid;

	vendor_param = snd_hdac_codec_read(hdev, vendor_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	if (vendor_param == -1 || vendor_param & INTEL_EN_DP12)
		return;

	/* enable DP1.2 mode */
	vendor_param |= INTEL_EN_DP12;
	vendor_param = snd_hdac_codec_read(hdev, vendor_nid, 0,
				INTEL_SET_VENDOR_VERB, vendor_param);
	if (vendor_param == -1)
		return;

}