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
struct machine_request_callback_data {scalar_t__ find_this_machine; TYPE_1__* result; } ;
struct TYPE_2__ {scalar_t__ machine; } ;
typedef  TYPE_1__ REGISTRY_PERSON_URL ;

/* Variables and functions */

__attribute__((used)) static int machine_request_callback(void *entry, void *data) {
    REGISTRY_PERSON_URL *mypu = (REGISTRY_PERSON_URL *)entry;
    struct machine_request_callback_data *myrdata = (struct machine_request_callback_data *)data;

    if(mypu->machine == myrdata->find_this_machine) {
        myrdata->result = mypu;
        return -1; // this will also stop the walk through
    }

    return 0; // continue
}