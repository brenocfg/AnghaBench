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
struct wined3d_occlusion_query {int /*<<< orphan*/  entry; struct wined3d_context* context; scalar_t__ id; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {int free_occlusion_query_count; int /*<<< orphan*/  occlusion_queries; scalar_t__* free_occlusion_queries; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 size_t ARB_OCCLUSION_QUERY ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,struct wined3d_context*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glGenQueries (int,scalar_t__*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void context_alloc_occlusion_query(struct wined3d_context *context, struct wined3d_occlusion_query *query)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (context->free_occlusion_query_count)
    {
        query->id = context->free_occlusion_queries[--context->free_occlusion_query_count];
    }
    else
    {
        if (gl_info->supported[ARB_OCCLUSION_QUERY])
        {
            GL_EXTCALL(glGenQueries(1, &query->id));
            checkGLcall("glGenQueries");

            TRACE("Allocated occlusion query %u in context %p.\n", query->id, context);
        }
        else
        {
            WARN("Occlusion queries not supported, not allocating query id.\n");
            query->id = 0;
        }
    }

    query->context = context;
    list_add_head(&context->occlusion_queries, &query->entry);
}