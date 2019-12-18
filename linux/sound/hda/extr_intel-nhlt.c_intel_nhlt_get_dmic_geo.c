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
typedef  scalar_t__ u8 ;
struct nhlt_vendor_dmic_array_config {unsigned int nb_mics; } ;
struct TYPE_2__ {scalar_t__ caps; } ;
struct nhlt_endpoint {scalar_t__ linktype; int length; TYPE_1__ config; } ;
struct nhlt_dmic_array_config {int array_type; } ;
struct nhlt_acpi_table {scalar_t__ endpoint_count; scalar_t__ desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MIC_ARRAY_2CH ; 
 unsigned int MIC_ARRAY_4CH ; 
 scalar_t__ NHLT_LINK_DMIC ; 
#define  NHLT_MIC_ARRAY_2CH_BIG 133 
#define  NHLT_MIC_ARRAY_2CH_SMALL 132 
#define  NHLT_MIC_ARRAY_4CH_1ST_GEOM 131 
#define  NHLT_MIC_ARRAY_4CH_2ND_GEOM 130 
#define  NHLT_MIC_ARRAY_4CH_L_SHAPED 129 
#define  NHLT_MIC_ARRAY_VENDOR_DEFINED 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 

int intel_nhlt_get_dmic_geo(struct device *dev, struct nhlt_acpi_table *nhlt)
{
	struct nhlt_endpoint *epnt;
	struct nhlt_dmic_array_config *cfg;
	struct nhlt_vendor_dmic_array_config *cfg_vendor;
	unsigned int dmic_geo = 0;
	u8 j;

	if (!nhlt)
		return 0;

	epnt = (struct nhlt_endpoint *)nhlt->desc;

	for (j = 0; j < nhlt->endpoint_count; j++) {
		if (epnt->linktype == NHLT_LINK_DMIC) {
			cfg = (struct nhlt_dmic_array_config  *)
					(epnt->config.caps);
			switch (cfg->array_type) {
			case NHLT_MIC_ARRAY_2CH_SMALL:
			case NHLT_MIC_ARRAY_2CH_BIG:
				dmic_geo = MIC_ARRAY_2CH;
				break;

			case NHLT_MIC_ARRAY_4CH_1ST_GEOM:
			case NHLT_MIC_ARRAY_4CH_L_SHAPED:
			case NHLT_MIC_ARRAY_4CH_2ND_GEOM:
				dmic_geo = MIC_ARRAY_4CH;
				break;
			case NHLT_MIC_ARRAY_VENDOR_DEFINED:
				cfg_vendor = (struct nhlt_vendor_dmic_array_config *)cfg;
				dmic_geo = cfg_vendor->nb_mics;
				break;
			default:
				dev_warn(dev, "undefined DMIC array_type 0x%0x\n",
					 cfg->array_type);
			}
		}
		epnt = (struct nhlt_endpoint *)((u8 *)epnt + epnt->length);
	}

	return dmic_geo;
}