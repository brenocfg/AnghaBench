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
struct TYPE_4__ {int /*<<< orphan*/  show_nr_samples; int /*<<< orphan*/  show_total_period; } ;
struct TYPE_3__ {int /*<<< orphan*/  show_nr_samples; int /*<<< orphan*/  show_total_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__config ; 
 TYPE_2__ annotation__default_options ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

void annotation_config__init(void)
{
	perf_config(annotation__config, NULL);

	annotation__default_options.show_total_period = symbol_conf.show_total_period;
	annotation__default_options.show_nr_samples   = symbol_conf.show_nr_samples;
}