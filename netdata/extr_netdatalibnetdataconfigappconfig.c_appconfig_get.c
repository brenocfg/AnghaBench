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
struct config_option {int flags; char* value; } ;
struct config {int dummy; } ;

/* Variables and functions */
 int CONFIG_VALUE_CHANGED ; 
 int CONFIG_VALUE_CHECKED ; 
 int CONFIG_VALUE_LOADED ; 
 int CONFIG_VALUE_USED ; 
 int /*<<< orphan*/  D_CONFIG ; 
 struct config_option* appconfig_option_index_find (struct section*,char const*,int /*<<< orphan*/ ) ; 
 struct section* appconfig_section_create (struct config*,char const*) ; 
 struct section* appconfig_section_find (struct config*,char const*) ; 
 struct config_option* appconfig_value_create (struct section*,char const*,char const*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

char *appconfig_get(struct config *root, const char *section, const char *name, const char *default_value)
{
    struct config_option *cv;

    debug(D_CONFIG, "request to get config in section '%s', name '%s', default_value '%s'", section, name, default_value);

    struct section *co = appconfig_section_find(root, section);
    if(!co) co = appconfig_section_create(root, section);

    cv = appconfig_option_index_find(co, name, 0);
    if(!cv) {
        cv = appconfig_value_create(co, name, default_value);
        if(!cv) return NULL;
    }
    cv->flags |= CONFIG_VALUE_USED;

    if((cv->flags & CONFIG_VALUE_LOADED) || (cv->flags & CONFIG_VALUE_CHANGED)) {
        // this is a loaded value from the config file
        // if it is different that the default, mark it
        if(!(cv->flags & CONFIG_VALUE_CHECKED)) {
            if(strcmp(cv->value, default_value) != 0) cv->flags |= CONFIG_VALUE_CHANGED;
            cv->flags |= CONFIG_VALUE_CHECKED;
        }
    }

    return(cv->value);
}