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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {void* mic2_micbias; void* mic1b_micbias; void* mic1a_micbias; void* mic2_type; void* mic1_type; } ;
struct ab8500_codec_platform_data {void* ear_cmv; TYPE_1__ amics; } ;

/* Variables and functions */
 void* AMIC_MICBIAS_VAMIC1 ; 
 void* AMIC_MICBIAS_VAMIC2 ; 
 void* AMIC_TYPE_DIFFERENTIAL ; 
 void* AMIC_TYPE_SINGLE_ENDED ; 
 void* EAR_CMV_0_95V ; 
 void* EAR_CMV_1_10V ; 
 void* EAR_CMV_1_27V ; 
 void* EAR_CMV_1_58V ; 
 void* EAR_CMV_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static void ab8500_codec_of_probe(struct device *dev, struct device_node *np,
				struct ab8500_codec_platform_data *codec)
{
	u32 value;

	if (of_property_read_bool(np, "stericsson,amic1-type-single-ended"))
		codec->amics.mic1_type = AMIC_TYPE_SINGLE_ENDED;
	else
		codec->amics.mic1_type = AMIC_TYPE_DIFFERENTIAL;

	if (of_property_read_bool(np, "stericsson,amic2-type-single-ended"))
		codec->amics.mic2_type = AMIC_TYPE_SINGLE_ENDED;
	else
		codec->amics.mic2_type = AMIC_TYPE_DIFFERENTIAL;

	/* Has a non-standard Vamic been requested? */
	if (of_property_read_bool(np, "stericsson,amic1a-bias-vamic2"))
		codec->amics.mic1a_micbias = AMIC_MICBIAS_VAMIC2;
	else
		codec->amics.mic1a_micbias = AMIC_MICBIAS_VAMIC1;

	if (of_property_read_bool(np, "stericsson,amic1b-bias-vamic2"))
		codec->amics.mic1b_micbias = AMIC_MICBIAS_VAMIC2;
	else
		codec->amics.mic1b_micbias = AMIC_MICBIAS_VAMIC1;

	if (of_property_read_bool(np, "stericsson,amic2-bias-vamic1"))
		codec->amics.mic2_micbias = AMIC_MICBIAS_VAMIC1;
	else
		codec->amics.mic2_micbias = AMIC_MICBIAS_VAMIC2;

	if (!of_property_read_u32(np, "stericsson,earpeice-cmv", &value)) {
		switch (value) {
		case 950 :
			codec->ear_cmv = EAR_CMV_0_95V;
			break;
		case 1100 :
			codec->ear_cmv = EAR_CMV_1_10V;
			break;
		case 1270 :
			codec->ear_cmv = EAR_CMV_1_27V;
			break;
		case 1580 :
			codec->ear_cmv = EAR_CMV_1_58V;
			break;
		default :
			codec->ear_cmv = EAR_CMV_UNKNOWN;
			dev_err(dev, "Unsuitable earpiece voltage found in DT\n");
		}
	} else {
		dev_warn(dev, "No earpiece voltage found in DT - using default\n");
		codec->ear_cmv = EAR_CMV_0_95V;
	}
}