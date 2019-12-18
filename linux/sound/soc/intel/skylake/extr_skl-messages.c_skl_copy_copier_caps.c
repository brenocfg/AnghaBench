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
struct TYPE_4__ {int caps_size; int /*<<< orphan*/  caps; } ;
struct skl_module_cfg {TYPE_2__ formats_config; } ;
struct TYPE_3__ {int config_length; int /*<<< orphan*/  config_data; } ;
struct skl_cpr_cfg {TYPE_1__ gtw_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skl_copy_copier_caps(struct skl_module_cfg *mconfig,
				struct skl_cpr_cfg *cpr_mconfig)
{
	if (mconfig->formats_config.caps_size == 0)
		return;

	memcpy(cpr_mconfig->gtw_cfg.config_data,
			mconfig->formats_config.caps,
			mconfig->formats_config.caps_size);

	cpr_mconfig->gtw_cfg.config_length =
			(mconfig->formats_config.caps_size) / 4;
}