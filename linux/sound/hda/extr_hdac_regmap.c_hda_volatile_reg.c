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
struct hdac_device {int /*<<< orphan*/  cache_coef; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  AC_VERB_GET_COEF_INDEX 141 
#define  AC_VERB_GET_DEVICE_LIST 140 
#define  AC_VERB_GET_DEVICE_SEL 139 
#define  AC_VERB_GET_HDMI_CHAN_SLOT 138 
#define  AC_VERB_GET_HDMI_CP_CTRL 137 
#define  AC_VERB_GET_HDMI_DIP_DATA 136 
#define  AC_VERB_GET_HDMI_DIP_INDEX 135 
#define  AC_VERB_GET_HDMI_DIP_SIZE 134 
#define  AC_VERB_GET_HDMI_DIP_XMIT 133 
#define  AC_VERB_GET_HDMI_ELDD 132 
#define  AC_VERB_GET_PIN_SENSE 131 
#define  AC_VERB_GET_POWER_STATE 130 
#define  AC_VERB_GET_PROC_COEF 129 
#define  AC_VERB_GET_PROC_STATE 128 
 struct hdac_device* dev_to_hdac_dev (struct device*) ; 
 unsigned int get_verb (unsigned int) ; 

__attribute__((used)) static bool hda_volatile_reg(struct device *dev, unsigned int reg)
{
	struct hdac_device *codec = dev_to_hdac_dev(dev);
	unsigned int verb = get_verb(reg);

	switch (verb) {
	case AC_VERB_GET_PROC_COEF:
		return !codec->cache_coef;
	case AC_VERB_GET_COEF_INDEX:
	case AC_VERB_GET_PROC_STATE:
	case AC_VERB_GET_POWER_STATE:
	case AC_VERB_GET_PIN_SENSE:
	case AC_VERB_GET_HDMI_DIP_SIZE:
	case AC_VERB_GET_HDMI_ELDD:
	case AC_VERB_GET_HDMI_DIP_INDEX:
	case AC_VERB_GET_HDMI_DIP_DATA:
	case AC_VERB_GET_HDMI_DIP_XMIT:
	case AC_VERB_GET_HDMI_CP_CTRL:
	case AC_VERB_GET_HDMI_CHAN_SLOT:
	case AC_VERB_GET_DEVICE_SEL:
	case AC_VERB_GET_DEVICE_LIST:	/* read-only volatile */
		return true;
	}

	return false;
}