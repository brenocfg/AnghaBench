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
struct lua_State {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct lua_State*) ; 

__attribute__((used)) static int mass_gc(struct lua_State *L)
{
    //struct MasscanWrapper *wrapper;
    //struct Masscan *masscan;

    UNUSEDPARM(L);

    //wrapper = luaL_checkudata(L, 1, MASSCAN_CLASS);
    //masscan = wrapper->masscan;

    /* I'm hot sure what I should do here for shutting down this object,
     * but I'm registering a garbage collection function anyway */
    
    return 0;
}