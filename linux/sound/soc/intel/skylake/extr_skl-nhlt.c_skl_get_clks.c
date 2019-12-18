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
typedef  int /*<<< orphan*/  u8 ;
struct skl_ssp_clk {int dummy; } ;
struct skl_dev {scalar_t__ nhlt; } ;
struct nhlt_fmt {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ caps; } ;
struct nhlt_endpoint {scalar_t__ linktype; int length; TYPE_1__ config; int /*<<< orphan*/  virtual_bus_id; } ;
struct nhlt_acpi_table {int endpoint_count; scalar_t__ desc; } ;

/* Variables and functions */
 scalar_t__ NHLT_LINK_SSP ; 
 int /*<<< orphan*/  skl_get_mclk (struct skl_dev*,struct skl_ssp_clk*,struct nhlt_fmt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_get_ssp_clks (struct skl_dev*,struct skl_ssp_clk*,struct nhlt_fmt*,int /*<<< orphan*/ ) ; 

void skl_get_clks(struct skl_dev *skl, struct skl_ssp_clk *ssp_clks)
{
	struct nhlt_acpi_table *nhlt = (struct nhlt_acpi_table *)skl->nhlt;
	struct nhlt_endpoint *epnt;
	struct nhlt_fmt *fmt;
	int i;
	u8 id;

	epnt = (struct nhlt_endpoint *)nhlt->desc;
	for (i = 0; i < nhlt->endpoint_count; i++) {
		if (epnt->linktype == NHLT_LINK_SSP) {
			id = epnt->virtual_bus_id;

			fmt = (struct nhlt_fmt *)(epnt->config.caps
					+ epnt->config.size);

			skl_get_ssp_clks(skl, ssp_clks, fmt, id);
			skl_get_mclk(skl, ssp_clks, fmt, id);
		}
		epnt = (struct nhlt_endpoint *)((u8 *)epnt + epnt->length);
	}
}