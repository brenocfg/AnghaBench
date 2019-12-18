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
 int check_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_loglevel (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_request_log_messages (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int script_enable_messages(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    check_loglevel(L, 1);
    const char *level = luaL_checkstring(L, 1);
    return check_error(L, mpv_request_log_messages(ctx->client, level));
}