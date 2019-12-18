#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  status; TYPE_6__* errorJmp; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  (* panic ) (TYPE_1__*) ;} ;
struct TYPE_10__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_7__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  LUAI_THROW (TYPE_1__*,TYPE_6__*) ; 
 int /*<<< orphan*/  cast_byte (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetstack (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void luaD_throw(lua_State*L,int errcode){
if(L->errorJmp){
L->errorJmp->status=errcode;
LUAI_THROW(L,L->errorJmp);
}
else{
L->status=cast_byte(errcode);
if(G(L)->panic){
resetstack(L,errcode);
G(L)->panic(L);
}
exit(EXIT_FAILURE);
}
}