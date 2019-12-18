#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct registry_person_url_callback_verify_machine_exists_data {int /*<<< orphan*/  count; int /*<<< orphan*/ * m; } ;
struct TYPE_2__ {int /*<<< orphan*/ * machine; } ;
typedef  TYPE_1__ REGISTRY_PERSON_URL ;
typedef  int /*<<< orphan*/  REGISTRY_MACHINE ;

/* Variables and functions */

__attribute__((used)) static inline int registry_person_url_callback_verify_machine_exists(void *entry, void *data) {
    struct registry_person_url_callback_verify_machine_exists_data *d = (struct registry_person_url_callback_verify_machine_exists_data *)data;
    REGISTRY_PERSON_URL *pu = (REGISTRY_PERSON_URL *)entry;
    REGISTRY_MACHINE *m = d->m;

    if(pu->machine == m)
        d->count++;

    return 0;
}