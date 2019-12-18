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
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
 char* config_get (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  error (char*,char*,char const*,char const*) ; 
 int simple_pattern_is_potential_name (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

int make_dns_decision(const char *section_name, const char *config_name, const char *default_value, SIMPLE_PATTERN *p)
{
    char *value = config_get(section_name,config_name,default_value);
    if(!strcmp("yes",value))
        return 1;
    if(!strcmp("no",value))
        return 0;
    if(strcmp("heuristic",value))
        error("Invalid configuration option '%s' for '%s'/'%s'. Valid options are 'yes', 'no' and 'heuristic'. Proceeding with 'heuristic'",
              value, section_name, config_name);
    return simple_pattern_is_potential_name(p);
}