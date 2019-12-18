#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* string; TYPE_2__* list; TYPE_1__* ba; int /*<<< orphan*/  flag; int /*<<< orphan*/  double_; int /*<<< orphan*/  int64; } ;
struct TYPE_9__ {int format; TYPE_3__ u; } ;
typedef  TYPE_4__ mpv_node ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_7__ {int num; int /*<<< orphan*/ * keys; TYPE_4__* values; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  MPV_FORMAT_BYTE_ARRAY 135 
#define  MPV_FORMAT_DOUBLE 134 
#define  MPV_FORMAT_FLAG 133 
#define  MPV_FORMAT_INT64 132 
#define  MPV_FORMAT_NODE_ARRAY 131 
#define  MPV_FORMAT_NODE_MAP 130 
#define  MPV_FORMAT_NONE 129 
#define  MPV_FORMAT_STRING 128 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pushnode(js_State *J, mpv_node *node)
{
    int len;
    switch (node->format) {
    case MPV_FORMAT_NONE:   js_pushnull(J); break;
    case MPV_FORMAT_STRING: js_pushstring(J, node->u.string); break;
    case MPV_FORMAT_INT64:  js_pushnumber(J, node->u.int64); break;
    case MPV_FORMAT_DOUBLE: js_pushnumber(J, node->u.double_); break;
    case MPV_FORMAT_FLAG:   js_pushboolean(J, node->u.flag); break;
    case MPV_FORMAT_BYTE_ARRAY:
        js_pushlstring(J, node->u.ba->data, node->u.ba->size);
        break;
    case MPV_FORMAT_NODE_ARRAY:
        js_newarray(J);
        len = node->u.list->num;
        for (int n = 0; n < len; n++) {
            pushnode(J, &node->u.list->values[n]);
            js_setindex(J, -2, n);
        }
        break;
    case MPV_FORMAT_NODE_MAP:
        js_newobject(J);
        len = node->u.list->num;
        for (int n = 0; n < len; n++) {
            pushnode(J, &node->u.list->values[n]);
            js_setproperty(J, -2, node->u.list->keys[n]);
        }
        break;
    default:
        js_pushstring(J, "[UNSUPPORTED_MPV_FORMAT]");
        break;
    }
}