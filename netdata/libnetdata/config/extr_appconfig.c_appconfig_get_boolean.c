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
 char* appconfig_get (struct config*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

int appconfig_get_boolean(struct config *root, const char *section, const char *name, int value)
{
    char *s;
    if(value) s = "yes";
    else s = "no";

    s = appconfig_get(root, section, name, s);
    if(!s) return value;

    if(!strcasecmp(s, "yes") || !strcasecmp(s, "true") || !strcasecmp(s, "on") || !strcasecmp(s, "auto") || !strcasecmp(s, "on demand")) return 1;
    return 0;
}