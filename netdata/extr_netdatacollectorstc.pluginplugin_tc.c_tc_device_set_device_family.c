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
struct tc_device {int family_updated; int /*<<< orphan*/ * family; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TC_LOOP ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strdupz (char*) ; 

__attribute__((used)) static inline void tc_device_set_device_family(struct tc_device *d, char *family) {
    freez(d->family);
    d->family = NULL;

    if(likely(family && *family && strcmp(d->id, family) != 0)) {
        debug(D_TC_LOOP, "TC: Setting device '%s' family to '%s'", d->id, family);
        d->family = strdupz(family);
        d->family_updated = 1;
    }
    // no need for null termination - it is already null
}