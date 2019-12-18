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
struct TYPE_4__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 char* bstrdup (char*) ; 
 int /*<<< orphan*/  config_set_item (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*,char*) ; 

void config_set_bool(config_t *config, const char *section, const char *name,
		     bool value)
{
	char *str = bstrdup(value ? "true" : "false");
	config_set_item(config, &config->sections, section, name, str);
}