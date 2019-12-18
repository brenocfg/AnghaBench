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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 scalar_t__ LUA_TNUMBER ; 
 int end_char ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int need_len ; 
 int run_input ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ uart_receive_rf ; 

__attribute__((used)) static int l_uart_on( lua_State* L )
{
  size_t sl, el;
  int32_t run = 1;
  uint8_t stack = 1;
  const char *method = luaL_checklstring( L, stack, &sl );
  stack++;
  if (method == NULL)
    return luaL_error( L, "wrong arg type" );

  if( lua_type( L, stack ) == LUA_TNUMBER )
  {
    need_len = ( uint16_t )luaL_checkinteger( L, stack );
    stack++;
    end_char = -1;
    if( need_len > 255 ){
      need_len = 255;
      return luaL_error( L, "wrong arg range" );
    }
  }
  else if(lua_isstring(L, stack))
  {
    const char *end = luaL_checklstring( L, stack, &el );
    stack++;
    if(el!=1){
      return luaL_error( L, "wrong arg range" );
    }
    end_char = (int16_t)end[0];
    need_len = 0;
  }

  // luaL_checkanyfunction(L, stack);
  if (lua_type(L, stack) == LUA_TFUNCTION || lua_type(L, stack) == LUA_TLIGHTFUNCTION){
    if ( lua_isnumber(L, stack+1) ){
      run = lua_tointeger(L, stack+1);
    }
    lua_pushvalue(L, stack);  // copy argument (func) to the top of stack
  } else {
    lua_pushnil(L);
  }
  if(sl == 4 && strcmp(method, "data") == 0){
    run_input = true;
    if(uart_receive_rf != LUA_NOREF){
      luaL_unref(L, LUA_REGISTRYINDEX, uart_receive_rf);
      uart_receive_rf = LUA_NOREF;
    }
    if(!lua_isnil(L, -1)){
      uart_receive_rf = luaL_ref(L, LUA_REGISTRYINDEX);
      if(run==0)
        run_input = false;
    } else {
      lua_pop(L, 1);
    }
  }else{
    lua_pop(L, 1);
    return luaL_error( L, "method not supported" );
  }
  return 0;
}