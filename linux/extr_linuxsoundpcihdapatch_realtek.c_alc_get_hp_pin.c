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
struct TYPE_3__ {scalar_t__ line_out_type; scalar_t__* line_out_pins; scalar_t__* hp_pins; } ;
struct TYPE_4__ {TYPE_1__ autocfg; } ;
struct alc_spec {TYPE_2__ gen; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ AC_JACK_HP_OUT ; 

__attribute__((used)) static hda_nid_t alc_get_hp_pin(struct alc_spec *spec)
{
	if (spec->gen.autocfg.hp_pins[0])
		return spec->gen.autocfg.hp_pins[0];
	if (spec->gen.autocfg.line_out_type == AC_JACK_HP_OUT)
		return spec->gen.autocfg.line_out_pins[0];
	return 0;
}