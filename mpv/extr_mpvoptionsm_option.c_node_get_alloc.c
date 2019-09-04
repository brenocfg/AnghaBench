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
struct TYPE_2__ {void* string; void* list; } ;
struct mpv_node {int format; TYPE_1__ u; } ;

/* Variables and functions */
#define  MPV_FORMAT_NODE_ARRAY 130 
#define  MPV_FORMAT_NODE_MAP 129 
#define  MPV_FORMAT_STRING 128 

void *node_get_alloc(struct mpv_node *node)
{
    // Assume it was allocated with copy_node(), which allocates all
    // sub-nodes with the parent node as talloc parent.
    switch (node->format) {
    case MPV_FORMAT_STRING:
        return node->u.string;
    case MPV_FORMAT_NODE_ARRAY:
    case MPV_FORMAT_NODE_MAP:
        return node->u.list;
    default:
        return NULL;
    }
}