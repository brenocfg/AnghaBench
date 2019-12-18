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
struct script_ctx {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* mpv_event_name (int) ; 
 scalar_t__ mpv_request_event (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int script_request_event(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    const char *event = luaL_checkstring(L, 1);
    bool enable = lua_toboolean(L, 2);
    // brute force event name -> id; stops working for events > assumed max
    int event_id = -1;
    for (int n = 0; n < 256; n++) {
        const char *name = mpv_event_name(n);
        if (name && strcmp(name, event) == 0) {
            event_id = n;
            break;
        }
    }
    lua_pushboolean(L, mpv_request_event(ctx->client, event_id, enable) >= 0);
    return 1;
}