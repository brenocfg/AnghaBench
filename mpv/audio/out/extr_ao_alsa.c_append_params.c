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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* talloc_asprintf (void*,char*,...) ; 
 char* talloc_strdup (void*,char const*) ; 

__attribute__((used)) static char *append_params(void *ta_parent, const char *device, const char *p)
{
    if (!p || !p[0])
        return talloc_strdup(ta_parent, device);

    int len = strlen(device);
    char *end = strchr(device, ':');
    if (!end) {
        /* no existing parameters: add it behind device name */
        return talloc_asprintf(ta_parent, "%s:%s", device, p);
    } else if (end[1] == '\0') {
        /* ":" but no parameters */
        return talloc_asprintf(ta_parent, "%s%s", device, p);
    } else if (end[1] == '{' && device[len - 1] == '}') {
        /* parameters in config syntax: add it inside the { } block */
        return talloc_asprintf(ta_parent, "%.*s %s}", len - 1, device, p);
    } else {
        /* a simple list of parameters: add it at the end of the list */
        return talloc_asprintf(ta_parent, "%s,%s", device, p);
    }
    abort();
}