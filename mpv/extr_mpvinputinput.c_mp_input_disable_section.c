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
struct input_ctx {int num_active_sections; struct active_section* active_sections; } ;
struct active_section {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct active_section*,int,int) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 char* normalize_section (struct input_ctx*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void mp_input_disable_section(struct input_ctx *ictx, char *name)
{
    input_lock(ictx);
    name = normalize_section(ictx, name);

    // Remove old section, or make sure it's on top if re-enabled
    for (int i = ictx->num_active_sections - 1; i >= 0; i--) {
        struct active_section *as = &ictx->active_sections[i];
        if (strcmp(as->name, name) == 0) {
            MP_TARRAY_REMOVE_AT(ictx->active_sections,
                                ictx->num_active_sections, i);
        }
    }
    input_unlock(ictx);
}