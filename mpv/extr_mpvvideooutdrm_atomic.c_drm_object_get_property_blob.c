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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_object {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/ * drmModePropertyBlobPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * drmModeGetPropertyBlob (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_object_get_property (struct drm_object*,char*,int /*<<< orphan*/ *) ; 

drmModePropertyBlobPtr drm_object_get_property_blob(struct drm_object *object, char *name)
{
   uint64_t blob_id;

   if (!drm_object_get_property(object, name, &blob_id)) {
       return drmModeGetPropertyBlob(object->fd, blob_id);
   }

   return NULL;
}