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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/ * lua_CFunction ;
struct TYPE_3__ {int /*<<< orphan*/ * f; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 TYPE_2__* clvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iscfunction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lua_CFunction lua_tocfunction(lua_State*L,int idx){
StkId o=index2adr(L,idx);
return(!iscfunction(o))?NULL:clvalue(o)->c.f;
}