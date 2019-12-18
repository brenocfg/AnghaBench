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
struct TYPE_2__ {int /*<<< orphan*/  show_hist_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int perf_ui_config(const char *var, const char *value)
{
	/* Add other config variables here. */
	if (!strcmp(var, "ui.show-headers"))
		symbol_conf.show_hist_headers = perf_config_bool(var, value);

	return 0;
}