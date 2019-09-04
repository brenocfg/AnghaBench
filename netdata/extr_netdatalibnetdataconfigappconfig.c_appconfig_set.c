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
struct section {int dummy; } ;
struct config_option {int /*<<< orphan*/  value; int /*<<< orphan*/  flags; } ;
struct config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_VALUE_CHANGED ; 
 int /*<<< orphan*/  CONFIG_VALUE_USED ; 
 int /*<<< orphan*/  D_CONFIG ; 
 struct config_option* appconfig_option_index_find (struct section*,char const*,int /*<<< orphan*/ ) ; 
 struct section* appconfig_section_create (struct config*,char const*) ; 
 struct section* appconfig_section_find (struct config*,char const*) ; 
 struct config_option* appconfig_value_create (struct section*,char const*,char const*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 

const char *appconfig_set(struct config *root, const char *section, const char *name, const char *value)
{
    struct config_option *cv;

    debug(D_CONFIG, "request to set config in section '%s', name '%s', value '%s'", section, name, value);

    struct section *co = appconfig_section_find(root, section);
    if(!co) co = appconfig_section_create(root, section);

    cv = appconfig_option_index_find(co, name, 0);
    if(!cv) cv = appconfig_value_create(co, name, value);
    cv->flags |= CONFIG_VALUE_USED;

    if(strcmp(cv->value, value) != 0) {
        cv->flags |= CONFIG_VALUE_CHANGED;

        freez(cv->value);
        cv->value = strdupz(value);
    }

    return value;
}