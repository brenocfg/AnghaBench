#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct drm_object {TYPE_2__* props; TYPE_1__** props_info; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int count_props; scalar_t__* prop_values; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,long long,...) ; 

void drm_object_print_info(struct mp_log *log, struct drm_object *object)
{
    mp_err(log, "Object ID = %d (type = %x) has %d properties\n",
           object->id, object->type, object->props->count_props);

    for (int i = 0; i < object->props->count_props; i++)
        mp_err(log, "    Property '%s' = %lld\n", object->props_info[i]->name,
               (long long)object->props->prop_values[i]);
}