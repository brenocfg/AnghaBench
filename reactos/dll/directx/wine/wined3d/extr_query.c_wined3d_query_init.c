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
struct wined3d_query_ops {int dummy; } ;
struct wined3d_query {int ref; int type; int /*<<< orphan*/  poll_list_entry; struct wined3d_query_ops const* query_ops; int /*<<< orphan*/  data_size; void const* data; int /*<<< orphan*/  state; struct wined3d_device* device; struct wined3d_parent_ops const* parent_ops; void* parent; } ;
struct wined3d_parent_ops {int dummy; } ;
struct wined3d_device {int dummy; } ;
typedef  enum wined3d_query_type { ____Placeholder_wined3d_query_type } wined3d_query_type ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_CREATED ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wined3d_query_init(struct wined3d_query *query, struct wined3d_device *device,
        enum wined3d_query_type type, const void *data, DWORD data_size,
        const struct wined3d_query_ops *query_ops, void *parent, const struct wined3d_parent_ops *parent_ops)
{
    query->ref = 1;
    query->parent = parent;
    query->parent_ops = parent_ops;
    query->device = device;
    query->state = QUERY_CREATED;
    query->type = type;
    query->data = data;
    query->data_size = data_size;
    query->query_ops = query_ops;
    list_init(&query->poll_list_entry);
}