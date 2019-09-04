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
struct destroy_callback {int /*<<< orphan*/  entry; void* ctx; scalar_t__ cb; } ;
struct d3drm_object {int /*<<< orphan*/  destroy_callbacks; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DRMOBJECTCALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRMERR_BADVALUE ; 
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 struct destroy_callback* heap_alloc (int) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT d3drm_object_add_destroy_callback(struct d3drm_object *object, D3DRMOBJECTCALLBACK cb, void *ctx)
{
    struct destroy_callback *callback;

    if (!cb)
        return D3DRMERR_BADVALUE;

    if (!(callback = heap_alloc(sizeof(*callback))))
        return E_OUTOFMEMORY;

    callback->cb = cb;
    callback->ctx = ctx;

    list_add_head(&object->destroy_callbacks, &callback->entry);
    return D3DRM_OK;
}