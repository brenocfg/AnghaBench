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
struct mp_log {int dummy; } ;
struct drm_object {int /*<<< orphan*/  id; TYPE_1__* props; int /*<<< orphan*/ * props_info; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int count_props; int /*<<< orphan*/ * props; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeGetProperty (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* drmModeObjectGetProperties (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_object_free_properties (struct drm_object*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/ * talloc_zero_size (int /*<<< orphan*/ *,int) ; 

int drm_object_create_properties(struct mp_log *log, int fd,
                                 struct drm_object *object)
{
    object->props = drmModeObjectGetProperties(fd, object->id, object->type);
    if (object->props) {
        object->props_info = talloc_zero_size(NULL, object->props->count_props
                                              * sizeof(object->props_info));
        if (object->props_info) {
            for (int i = 0; i < object->props->count_props; i++)
                object->props_info[i] = drmModeGetProperty(fd, object->props->props[i]);
        } else {
            mp_err(log, "Out of memory\n");
            goto fail;
        }
    } else {
        mp_err(log, "Failed to retrieve properties for object id %d\n", object->id);
        goto fail;
    }

    return 0;

  fail:
    drm_object_free_properties(object);
    return -1;
}