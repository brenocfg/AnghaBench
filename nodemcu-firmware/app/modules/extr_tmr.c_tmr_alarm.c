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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  tmr_register (int /*<<< orphan*/ *) ; 
 int tmr_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tmr_alarm(lua_State* L){
	tmr_register(L);
	return tmr_start(L);
}