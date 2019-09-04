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
typedef  double lua_Number ;
typedef  int /*<<< orphan*/  UB ;
typedef  int /*<<< orphan*/  U64 ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static UB barg(lua_State*L,int idx){
union{lua_Number n;U64 b;}bn;
bn.n=lua_tonumber(L,idx)+6755399441055744.0;
if(bn.n==0.0&&!lua_isnumber(L,idx))luaL_typerror(L,idx,"number");
return(UB)bn.b;
}