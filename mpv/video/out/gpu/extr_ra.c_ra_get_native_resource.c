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
struct ra_native_resource {void* data; int /*<<< orphan*/  name; } ;
struct ra {int num_native_resources; struct ra_native_resource* native_resources; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void *ra_get_native_resource(struct ra *ra, const char *name)
{
    for (int n = 0; n < ra->num_native_resources; n++) {
        struct ra_native_resource *r = &ra->native_resources[n];
        if (strcmp(r->name, name) == 0)
            return r->data;
    }

    return NULL;
}