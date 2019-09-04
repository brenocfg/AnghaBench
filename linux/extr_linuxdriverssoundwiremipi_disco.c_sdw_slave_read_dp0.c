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
struct sdw_slave {int /*<<< orphan*/  dev; } ;
struct sdw_dp0_prop {int num_words; void* device_interrupts; void* simple_ch_prep_sm; void* flow_controlled; int /*<<< orphan*/ * words; int /*<<< orphan*/  min_word; int /*<<< orphan*/  max_word; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 void* fwnode_property_read_bool (struct fwnode_handle*,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,int /*<<< orphan*/ *) ; 
 int fwnode_property_read_u32_array (struct fwnode_handle*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sdw_slave_read_dp0(struct sdw_slave *slave,
		struct fwnode_handle *port, struct sdw_dp0_prop *dp0)
{
	int nval;

	fwnode_property_read_u32(port, "mipi-sdw-port-max-wordlength",
			&dp0->max_word);

	fwnode_property_read_u32(port, "mipi-sdw-port-min-wordlength",
			&dp0->min_word);

	nval = fwnode_property_read_u32_array(port,
			"mipi-sdw-port-wordlength-configs", NULL, 0);
	if (nval > 0) {

		dp0->num_words = nval;
		dp0->words = devm_kcalloc(&slave->dev,
				dp0->num_words, sizeof(*dp0->words),
				GFP_KERNEL);
		if (!dp0->words)
			return -ENOMEM;

		fwnode_property_read_u32_array(port,
				"mipi-sdw-port-wordlength-configs",
				dp0->words, dp0->num_words);
	}

	dp0->flow_controlled = fwnode_property_read_bool(
			port, "mipi-sdw-bra-flow-controlled");

	dp0->simple_ch_prep_sm = fwnode_property_read_bool(
			port, "mipi-sdw-simplified-channel-prepare-sm");

	dp0->device_interrupts = fwnode_property_read_bool(
			port, "mipi-sdw-imp-def-dp0-interrupts-supported");

	return 0;
}