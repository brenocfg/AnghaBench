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
struct tc_device {int name_updated; int /*<<< orphan*/ * name; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TC_LOOP ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tc_device_set_device_name(struct tc_device *d, char *name) {
    if(unlikely(!name || !*name)) return;

    if(d->name) {
        if(!strcmp(d->name, name)) return;
        freez(d->name);
        d->name = NULL;
    }

    if(likely(name && *name && strcmp(d->id, name) != 0)) {
        debug(D_TC_LOOP, "TC: Setting device '%s' name to '%s'", d->id, name);
        d->name = strdupz(name);
        d->name_updated = 1;
    }
}