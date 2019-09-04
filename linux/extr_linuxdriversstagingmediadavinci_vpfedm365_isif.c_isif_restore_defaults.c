#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vpfe_isif_raw_config {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  vcpat; int /*<<< orphan*/  hcpat_even; int /*<<< orphan*/  hcpat_odd; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_8__ {TYPE_1__ scale_fact; int /*<<< orphan*/  corr_shft; } ;
struct TYPE_12__ {TYPE_3__ culling; TYPE_2__ linearize; } ;
struct TYPE_10__ {TYPE_6__ config_params; } ;
struct TYPE_11__ {int /*<<< orphan*/  base_addr; TYPE_4__ bayer; } ;
struct vpfe_isif_device {TYPE_5__ isif_cfg; } ;
typedef  enum vpss_ccdc_source_sel { ____Placeholder_vpss_ccdc_source_sel } vpss_ccdc_source_sel ;

/* Variables and functions */
 int CULH ; 
 int CULV ; 
 int /*<<< orphan*/  ISIF_CULLING_HCAPT_EVEN ; 
 int /*<<< orphan*/  ISIF_CULLING_HCAPT_ODD ; 
 int /*<<< orphan*/  ISIF_CULLING_VCAPT ; 
 int /*<<< orphan*/  VPFE_ISIF_NO_SHIFT ; 
 int /*<<< orphan*/  VPSS_BL_CLOCK ; 
 int VPSS_CCDCIN ; 
 int /*<<< orphan*/  VPSS_CCDC_CLOCK ; 
 int /*<<< orphan*/  VPSS_IPIPEIF_CLOCK ; 
 int /*<<< orphan*/  isif_config_gain_offset (struct vpfe_isif_device*) ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vpss_enable_clock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vpss_select_ccdc_source (int) ; 

__attribute__((used)) static void isif_restore_defaults(struct vpfe_isif_device *isif)
{
	enum vpss_ccdc_source_sel source = VPSS_CCDCIN;
	int i;

	memset(&isif->isif_cfg.bayer.config_params, 0,
	       sizeof(struct vpfe_isif_raw_config));

	isif->isif_cfg.bayer.config_params.linearize.corr_shft =
					VPFE_ISIF_NO_SHIFT;
	isif->isif_cfg.bayer.config_params.linearize.scale_fact.integer = 1;
	isif->isif_cfg.bayer.config_params.culling.hcpat_odd =
			ISIF_CULLING_HCAPT_ODD;
	isif->isif_cfg.bayer.config_params.culling.hcpat_even =
			ISIF_CULLING_HCAPT_EVEN;
	isif->isif_cfg.bayer.config_params.culling.vcpat = ISIF_CULLING_VCAPT;
	/* Enable clock to ISIF, IPIPEIF and BL */
	vpss_enable_clock(VPSS_CCDC_CLOCK, 1);
	vpss_enable_clock(VPSS_IPIPEIF_CLOCK, 1);
	vpss_enable_clock(VPSS_BL_CLOCK, 1);

	/* set all registers to default value */
	for (i = 0; i <= 0x1f8; i += 4)
		isif_write(isif->isif_cfg.base_addr, 0, i);
	/* no culling support */
	isif_write(isif->isif_cfg.base_addr, 0xffff, CULH);
	isif_write(isif->isif_cfg.base_addr, 0xff, CULV);

	/* Set default offset and gain */
	isif_config_gain_offset(isif);
	vpss_select_ccdc_source(source);
}