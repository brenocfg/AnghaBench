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
struct TYPE_2__ {scalar_t__ caps_size; int /*<<< orphan*/  caps; } ;
struct skl_module_cfg {TYPE_1__ formats_config; } ;
struct skl_dev {int dummy; } ;
struct skl_base_cfg {int dummy; } ;
struct skl_algo_cfg {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skl_set_base_module_format (struct skl_dev*,struct skl_module_cfg*,struct skl_base_cfg*) ; 

__attribute__((used)) static void skl_set_algo_format(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_algo_cfg *algo_mcfg)
{
	struct skl_base_cfg *base_cfg = (struct skl_base_cfg *)algo_mcfg;

	skl_set_base_module_format(skl, mconfig, base_cfg);

	if (mconfig->formats_config.caps_size == 0)
		return;

	memcpy(algo_mcfg->params,
			mconfig->formats_config.caps,
			mconfig->formats_config.caps_size);

}