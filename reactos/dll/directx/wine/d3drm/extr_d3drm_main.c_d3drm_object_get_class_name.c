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
struct d3drm_object {int /*<<< orphan*/  classname; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

HRESULT d3drm_object_get_class_name(struct d3drm_object *object, DWORD *size, char *name)
{
    DWORD req_size;

    if (!size)
        return E_INVALIDARG;

    req_size = strlen(object->classname) + 1;
    if (name && *size < req_size)
        return E_INVALIDARG;

    *size = req_size;

    if (name)
        memcpy(name, object->classname, req_size);

    return D3DRM_OK;
}