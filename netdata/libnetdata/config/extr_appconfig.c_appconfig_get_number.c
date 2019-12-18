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
 int /*<<< orphan*/  sprintf (char*,char*,long long) ; 
 long long strtoll (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

long long appconfig_get_number(struct config *root, const char *section, const char *name, long long value)
{
    char buffer[100], *s;
    sprintf(buffer, "%lld", value);

    s = appconfig_get(root, section, name, buffer);
    if(!s) return value;

    return strtoll(s, NULL, 0);
}