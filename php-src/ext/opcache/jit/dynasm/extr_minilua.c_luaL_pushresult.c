#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lvl; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  emptybuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void luaL_pushresult(luaL_Buffer*B){
emptybuffer(B);
lua_concat(B->L,B->lvl);
B->lvl=1;
}