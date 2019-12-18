#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_checkvalidindex (TYPE_1__*,scalar_t__) ; 
 scalar_t__ index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void lua_remove(lua_State*L,int idx){
StkId p;
p=index2adr(L,idx);
api_checkvalidindex(L,p);
while(++p<L->top)setobj(L,p-1,p);
L->top--;
}