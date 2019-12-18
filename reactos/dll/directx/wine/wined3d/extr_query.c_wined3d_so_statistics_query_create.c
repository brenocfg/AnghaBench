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
struct wined3d_so_statistics_query {unsigned int stream_idx; struct wined3d_query query; int /*<<< orphan*/  statistics; } ;
struct wined3d_parent_ops {int dummy; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device {TYPE_1__* adapter; } ;
typedef  enum wined3d_query_type { ____Placeholder_wined3d_query_type } wined3d_query_type ;
struct TYPE_2__ {struct wined3d_gl_info gl_info; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ARB_TRANSFORM_FEEDBACK3 ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3DERR_NOTAVAILABLE ; 
 size_t WINED3D_GL_PRIMITIVE_QUERY ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 int WINED3D_QUERY_TYPE_SO_STATISTICS_STREAM0 ; 
 int WINED3D_QUERY_TYPE_SO_STATISTICS_STREAM3 ; 
 struct wined3d_so_statistics_query* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  so_statistics_query_ops ; 
 int /*<<< orphan*/  wined3d_query_init (struct wined3d_query*,struct wined3d_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*,struct wined3d_parent_ops const*) ; 

__attribute__((used)) static HRESULT wined3d_so_statistics_query_create(struct wined3d_device *device,
        enum wined3d_query_type type, void *parent, const struct wined3d_parent_ops *parent_ops,
        struct wined3d_query **query)
{
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_so_statistics_query *object;
    unsigned int stream_idx;

    if (WINED3D_QUERY_TYPE_SO_STATISTICS_STREAM0 <= type && type <= WINED3D_QUERY_TYPE_SO_STATISTICS_STREAM3)
        stream_idx = type - WINED3D_QUERY_TYPE_SO_STATISTICS_STREAM0;
    else
        return WINED3DERR_NOTAVAILABLE;

    TRACE("device %p, type %#x, parent %p, parent_ops %p, query %p.\n",
            device, type, parent, parent_ops, query);

    if (!gl_info->supported[WINED3D_GL_PRIMITIVE_QUERY])
    {
        WARN("OpenGL implementation does not support primitive queries.\n");
        return WINED3DERR_NOTAVAILABLE;
    }
    if (!gl_info->supported[ARB_TRANSFORM_FEEDBACK3])
    {
        WARN("OpenGL implementation does not support indexed queries.\n");
        return WINED3DERR_NOTAVAILABLE;
    }

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    wined3d_query_init(&object->query, device, type, &object->statistics,
            sizeof(object->statistics), &so_statistics_query_ops, parent, parent_ops);
    object->stream_idx = stream_idx;

    TRACE("Created query %p.\n", object);
    *query = &object->query;

    return WINED3D_OK;
}