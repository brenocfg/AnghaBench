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
struct TYPE_8__ {TYPE_2__* ba; TYPE_1__* list; int /*<<< orphan*/  flag; int /*<<< orphan*/  double_; int /*<<< orphan*/  int64; int /*<<< orphan*/  string; } ;
struct TYPE_9__ {int format; TYPE_3__ u; } ;
typedef  TYPE_4__ mpv_node ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int num; TYPE_4__* values; int /*<<< orphan*/ * keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  MPV_FORMAT_BYTE_ARRAY 135 
#define  MPV_FORMAT_DOUBLE 134 
#define  MPV_FORMAT_FLAG 133 
#define  MPV_FORMAT_INT64 132 
#define  MPV_FORMAT_NODE_ARRAY 131 
#define  MPV_FORMAT_NODE_MAP 130 
#define  MPV_FORMAT_NONE 129 
#define  MPV_FORMAT_STRING 128 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pushnode(lua_State *L, mpv_node *node)
{
    luaL_checkstack(L, 6, "stack overflow");

    switch (node->format) {
    case MPV_FORMAT_STRING:
        lua_pushstring(L, node->u.string);
        break;
    case MPV_FORMAT_INT64:
        lua_pushnumber(L, node->u.int64);
        break;
    case MPV_FORMAT_DOUBLE:
        lua_pushnumber(L, node->u.double_);
        break;
    case MPV_FORMAT_NONE:
        lua_pushnil(L);
        break;
    case MPV_FORMAT_FLAG:
        lua_pushboolean(L, node->u.flag);
        break;
    case MPV_FORMAT_NODE_ARRAY:
        lua_newtable(L); // table
        lua_getfield(L, LUA_REGISTRYINDEX, "ARRAY"); // table mt
        lua_setmetatable(L, -2); // table
        for (int n = 0; n < node->u.list->num; n++) {
            pushnode(L, &node->u.list->values[n]); // table value
            lua_rawseti(L, -2, n + 1); // table
        }
        break;
    case MPV_FORMAT_NODE_MAP:
        lua_newtable(L); // table
        lua_getfield(L, LUA_REGISTRYINDEX, "MAP"); // table mt
        lua_setmetatable(L, -2); // table
        for (int n = 0; n < node->u.list->num; n++) {
            lua_pushstring(L, node->u.list->keys[n]); // table key
            pushnode(L, &node->u.list->values[n]); // table key value
            lua_rawset(L, -3);
        }
        break;
    case MPV_FORMAT_BYTE_ARRAY:
        lua_pushlstring(L, node->u.ba->data, node->u.ba->size);
        break;
    default:
        // unknown value - what do we do?
        // for now, set a unique dummy value
        lua_newtable(L); // table
        lua_getfield(L, LUA_REGISTRYINDEX, "UNKNOWN_TYPE");
        lua_setmetatable(L, -2); // table
        break;
    }
}