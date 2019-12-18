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
struct wined3d_query {int dummy; } ;
struct wined3d_timestamp_query {struct wined3d_query query; int /*<<< orphan*/  timestamp; } ;
struct wined3d_parent_ops {int dummy; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device {TYPE_1__* adapter; } ;
typedef  enum wined3d_query_type { ____Placeholder_wined3d_query_type } wined3d_query_type ;
struct TYPE_2__ {struct wined3d_gl_info gl_info; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ARB_TIMER_QUERY ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3DERR_NOTAVAILABLE ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 struct wined3d_timestamp_query* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  timestamp_query_ops ; 
 int /*<<< orphan*/  wined3d_query_init (struct wined3d_query*,struct wined3d_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*,struct wined3d_parent_ops const*) ; 

__attribute__((used)) static HRESULT wined3d_timestamp_query_create(struct wined3d_device *device,
        enum wined3d_query_type type, void *parent, const struct wined3d_parent_ops *parent_ops,
        struct wined3d_query **query)
{
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_timestamp_query *object;

    TRACE("device %p, type %#x, parent %p, parent_ops %p, query %p.\n",
            device, type, parent, parent_ops, query);

    if (!gl_info->supported[ARB_TIMER_QUERY])
    {
        WARN("Unsupported in local OpenGL implementation: ARB_TIMER_QUERY.\n");
        return WINED3DERR_NOTAVAILABLE;
    }

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    wined3d_query_init(&object->query, device, type, &object->timestamp,
            sizeof(object->timestamp), &timestamp_query_ops, parent, parent_ops);

    TRACE("Created query %p.\n", object);
    *query = &object->query;

    return WINED3D_OK;
}