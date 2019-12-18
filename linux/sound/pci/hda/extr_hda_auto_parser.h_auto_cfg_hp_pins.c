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
struct auto_pin_cfg {scalar_t__ line_out_type; int /*<<< orphan*/  const* hp_pins; int /*<<< orphan*/  const* line_out_pins; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 

__attribute__((used)) static inline const hda_nid_t *auto_cfg_hp_pins(const struct auto_pin_cfg *cfg)
{
	return (cfg->line_out_type == AUTO_PIN_HP_OUT) ?
	       cfg->line_out_pins : cfg->hp_pins;
}