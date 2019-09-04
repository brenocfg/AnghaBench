#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lua_State {int dummy; } ;
struct TCP_ConnectionTable {TYPE_1__* banner1; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (TYPE_1__*) ;} ;
struct TYPE_3__ {struct lua_State* L; } ;

/* Variables and functions */
 TYPE_2__ banner_scripting ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void scripting_init_tcp(struct TCP_ConnectionTable *tcpcon, struct lua_State *L)
{
    tcpcon->banner1->L = L;
    
    banner_scripting.init(tcpcon->banner1);
}