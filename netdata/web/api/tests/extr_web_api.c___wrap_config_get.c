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
 char* CONFIG_SECTION_WEB ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

char *__wrap_config_get(struct config *root, const char *section, const char *name, const char *default_value)
{
    if (!strcmp(section, CONFIG_SECTION_WEB) && !strcmp(name, "web files owner"))
        return "netdata";
    return "UNKNOWN FIX ME";
}