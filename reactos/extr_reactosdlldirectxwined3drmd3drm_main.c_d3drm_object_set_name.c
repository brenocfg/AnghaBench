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
struct d3drm_object {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

HRESULT d3drm_object_set_name(struct d3drm_object *object, const char *name)
{
    DWORD req_size;

    heap_free(object->name);
    object->name = NULL;

    if (name)
    {
        req_size = strlen(name) + 1;
        if (!(object->name = heap_alloc(req_size)))
            return E_OUTOFMEMORY;
        memcpy(object->name, name, req_size);
    }

    return D3DRM_OK;
}