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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct wined3d_pipeline_statistics_query {int /*<<< orphan*/  entry; struct wined3d_context* context; TYPE_1__ u; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {int free_pipeline_statistics_query_count; int /*<<< orphan*/  pipeline_statistics_queries; TYPE_1__* free_pipeline_statistics_queries; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glGenQueries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void context_alloc_pipeline_statistics_query(struct wined3d_context *context,
        struct wined3d_pipeline_statistics_query *query)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (context->free_pipeline_statistics_query_count)
    {
        query->u = context->free_pipeline_statistics_queries[--context->free_pipeline_statistics_query_count];
    }
    else
    {
        GL_EXTCALL(glGenQueries(ARRAY_SIZE(query->u.id), query->u.id));
        checkGLcall("glGenQueries");
    }

    query->context = context;
    list_add_head(&context->pipeline_statistics_queries, &query->entry);
}