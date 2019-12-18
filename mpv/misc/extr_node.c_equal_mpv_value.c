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
struct mpv_byte_array {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int num; char** keys; void const* values; } ;
typedef  TYPE_1__ mpv_node_list ;
typedef  int mpv_format ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  MPV_FORMAT_BYTE_ARRAY 137 
#define  MPV_FORMAT_DOUBLE 136 
#define  MPV_FORMAT_FLAG 135 
#define  MPV_FORMAT_INT64 134 
#define  MPV_FORMAT_NODE 133 
#define  MPV_FORMAT_NODE_ARRAY 132 
#define  MPV_FORMAT_NODE_MAP 131 
#define  MPV_FORMAT_NONE 130 
#define  MPV_FORMAT_OSD_STRING 129 
#define  MPV_FORMAT_STRING 128 
 int /*<<< orphan*/  abort () ; 
 int equal_mpv_node (void const*,void const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

bool equal_mpv_value(const void *a, const void *b, mpv_format format)
{
    switch (format) {
    case MPV_FORMAT_NONE:
        return true;
    case MPV_FORMAT_STRING:
    case MPV_FORMAT_OSD_STRING:
        return strcmp(*(char **)a, *(char **)b) == 0;
    case MPV_FORMAT_FLAG:
        return *(int *)a == *(int *)b;
    case MPV_FORMAT_INT64:
        return *(int64_t *)a == *(int64_t *)b;
    case MPV_FORMAT_DOUBLE:
        return *(double *)a == *(double *)b;
    case MPV_FORMAT_NODE:
        return equal_mpv_node(a, b);
    case MPV_FORMAT_BYTE_ARRAY: {
        const struct mpv_byte_array *a_r = a, *b_r = b;
        if (a_r->size != b_r->size)
            return false;
        return memcmp(a_r->data, b_r->data, a_r->size) == 0;
    }
    case MPV_FORMAT_NODE_ARRAY:
    case MPV_FORMAT_NODE_MAP:
    {
        mpv_node_list *l_a = *(mpv_node_list **)a, *l_b = *(mpv_node_list **)b;
        if (l_a->num != l_b->num)
            return false;
        for (int n = 0; n < l_a->num; n++) {
            if (format == MPV_FORMAT_NODE_MAP) {
                if (strcmp(l_a->keys[n], l_b->keys[n]) != 0)
                    return false;
            }
            if (!equal_mpv_node(&l_a->values[n], &l_b->values[n]))
                return false;
        }
        return true;
    }
    }
    abort(); // supposed to be able to handle all defined types
}