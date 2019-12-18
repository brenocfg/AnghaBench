#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defaults; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  config_set_item (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 

void config_set_default_string(config_t *config, const char *section,
			       const char *name, const char *value)
{
	if (!value)
		value = "";
	config_set_item(config, &config->defaults, section, name,
			bstrdup(value));
}