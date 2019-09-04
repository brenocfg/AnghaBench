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
struct hdmi_vendor_infoframe {int version; int /*<<< orphan*/  s3d_struct; int /*<<< orphan*/  oui; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_3D_STRUCTURE_INVALID ; 
 int /*<<< orphan*/  HDMI_IEEE_OUI ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_VENDOR ; 
 int /*<<< orphan*/  memset (struct hdmi_vendor_infoframe*,int /*<<< orphan*/ ,int) ; 

int hdmi_vendor_infoframe_init(struct hdmi_vendor_infoframe *frame)
{
	memset(frame, 0, sizeof(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_VENDOR;
	frame->version = 1;

	frame->oui = HDMI_IEEE_OUI;

	/*
	 * 0 is a valid value for s3d_struct, so we use a special "not set"
	 * value
	 */
	frame->s3d_struct = HDMI_3D_STRUCTURE_INVALID;

	return 0;
}