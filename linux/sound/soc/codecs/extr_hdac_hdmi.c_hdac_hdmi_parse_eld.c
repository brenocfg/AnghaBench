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
struct TYPE_3__ {unsigned int spk_alloc; } ;
struct TYPE_4__ {unsigned int* eld_buffer; TYPE_1__ info; } ;
struct hdac_hdmi_port {TYPE_2__ eld; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DRM_ELD_CEA_EDID_VER_MNL ; 
 unsigned int DRM_ELD_MNL_MASK ; 
 unsigned int DRM_ELD_MNL_SHIFT ; 
 size_t DRM_ELD_SPEAKER ; 
 size_t DRM_ELD_VER ; 
 unsigned int DRM_ELD_VER_MASK ; 
 unsigned int DRM_ELD_VER_SHIFT ; 
 int EINVAL ; 
 unsigned int ELD_MAX_MNL ; 
 unsigned int ELD_VER_CEA_861D ; 
 unsigned int ELD_VER_PARTIAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static int hdac_hdmi_parse_eld(struct hdac_device *hdev,
			struct hdac_hdmi_port *port)
{
	unsigned int ver, mnl;

	ver = (port->eld.eld_buffer[DRM_ELD_VER] & DRM_ELD_VER_MASK)
						>> DRM_ELD_VER_SHIFT;

	if (ver != ELD_VER_CEA_861D && ver != ELD_VER_PARTIAL) {
		dev_err(&hdev->dev, "HDMI: Unknown ELD version %d\n", ver);
		return -EINVAL;
	}

	mnl = (port->eld.eld_buffer[DRM_ELD_CEA_EDID_VER_MNL] &
		DRM_ELD_MNL_MASK) >> DRM_ELD_MNL_SHIFT;

	if (mnl > ELD_MAX_MNL) {
		dev_err(&hdev->dev, "HDMI: MNL Invalid %d\n", mnl);
		return -EINVAL;
	}

	port->eld.info.spk_alloc = port->eld.eld_buffer[DRM_ELD_SPEAKER];

	return 0;
}