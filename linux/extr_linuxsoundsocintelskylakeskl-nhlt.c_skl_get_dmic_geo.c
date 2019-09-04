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
typedef  scalar_t__ u8 ;
struct skl {TYPE_1__* pci; scalar_t__ nhlt; } ;
struct TYPE_4__ {scalar_t__ caps; } ;
struct nhlt_endpoint {scalar_t__ linktype; int length; TYPE_2__ config; } ;
struct nhlt_dmic_array_config {int array_type; } ;
struct nhlt_acpi_table {scalar_t__ endpoint_count; scalar_t__ desc; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 unsigned int MIC_ARRAY_2CH ; 
 unsigned int MIC_ARRAY_4CH ; 
 scalar_t__ NHLT_LINK_DMIC ; 
#define  NHLT_MIC_ARRAY_2CH_BIG 132 
#define  NHLT_MIC_ARRAY_2CH_SMALL 131 
#define  NHLT_MIC_ARRAY_4CH_1ST_GEOM 130 
#define  NHLT_MIC_ARRAY_4CH_2ND_GEOM 129 
#define  NHLT_MIC_ARRAY_4CH_L_SHAPED 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 

int skl_get_dmic_geo(struct skl *skl)
{
	struct nhlt_acpi_table *nhlt = (struct nhlt_acpi_table *)skl->nhlt;
	struct nhlt_endpoint *epnt;
	struct nhlt_dmic_array_config *cfg;
	struct device *dev = &skl->pci->dev;
	unsigned int dmic_geo = 0;
	u8 j;

	epnt = (struct nhlt_endpoint *)nhlt->desc;

	for (j = 0; j < nhlt->endpoint_count; j++) {
		if (epnt->linktype == NHLT_LINK_DMIC) {
			cfg = (struct nhlt_dmic_array_config  *)
					(epnt->config.caps);
			switch (cfg->array_type) {
			case NHLT_MIC_ARRAY_2CH_SMALL:
			case NHLT_MIC_ARRAY_2CH_BIG:
				dmic_geo |= MIC_ARRAY_2CH;
				break;

			case NHLT_MIC_ARRAY_4CH_1ST_GEOM:
			case NHLT_MIC_ARRAY_4CH_L_SHAPED:
			case NHLT_MIC_ARRAY_4CH_2ND_GEOM:
				dmic_geo |= MIC_ARRAY_4CH;
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