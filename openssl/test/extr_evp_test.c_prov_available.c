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
 scalar_t__ OSSL_PROVIDER_available (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static int prov_available(char *providers)
{
    char *p;
    int more = 1;

    while (more) {
        for (; isspace(*providers); providers++)
            continue;
        if (*providers == '\0')
            break;               /* End of the road */
        for (p = providers; *p != '\0' && !isspace(*p); p++)
            continue;
        if (*p == '\0')
            more = 0;
        else
            *p = '\0';
        if (OSSL_PROVIDER_available(NULL, providers))
            return 1;            /* Found one */
    }
    return 0;
}