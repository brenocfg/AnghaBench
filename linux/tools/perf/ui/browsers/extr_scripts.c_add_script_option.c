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
struct script_config {char const** names; size_t index; int /*<<< orphan*/  extra_format; int /*<<< orphan*/  perf; int /*<<< orphan*/ * paths; } ;
struct TYPE_2__ {scalar_t__ inline_name; } ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int add_script_option(const char *name, const char *opt,
			     struct script_config *c)
{
	c->names[c->index] = name;
	if (asprintf(&c->paths[c->index],
		     "%s script %s -F +metric %s %s",
		     c->perf, opt, symbol_conf.inline_name ? " --inline" : "",
		     c->extra_format) < 0)
		return -1;
	c->index++;
	return 0;
}