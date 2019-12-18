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
struct config {int dummy; } ;

/* Variables and functions */
 char* appconfig_get (struct config*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  config_parse_duration (char const*,int*) ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,char const*) ; 

int appconfig_get_duration(struct config *root, const char *section, const char *name, const char *value)
{
    int result = 0;
    const char *s;

    s = appconfig_get(root, section, name, value);
    if(!s) goto fallback;

    if(!config_parse_duration(s, &result)) {
        error("config option '[%s].%s = %s' is configured with an valid duration", section, name, s);
        goto fallback;
    }

    return result;

    fallback:
    if(!config_parse_duration(value, &result))
        error("INTERNAL ERROR: default duration supplied for option '[%s].%s = %s' is not a valid duration", section, name, value);

    return result;
}