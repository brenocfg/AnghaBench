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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_object {TYPE_2__** props_info; int /*<<< orphan*/  id; TYPE_1__* props; } ;
typedef  int /*<<< orphan*/  drmModeAtomicReq ;
struct TYPE_4__ {int /*<<< orphan*/  prop_id; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int count_props; } ;

/* Variables and functions */
 int EINVAL ; 
 int drmModeAtomicAddProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 

int drm_object_set_property(drmModeAtomicReq *request, struct drm_object *object,
                            char *name, uint64_t value)
{
   for (int i = 0; i < object->props->count_props; i++) {
       if (strcasecmp(name, object->props_info[i]->name) == 0) {
           return drmModeAtomicAddProperty(request, object->id,
                                           object->props_info[i]->prop_id, value);
       }
   }

   return -EINVAL;
}