#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int isr_throttled; int vu_freq; void* pin; TYPE_1__* bufs; void* cb_vu_ref; void* cb_stopped_ref; void* cb_paused_ref; void* cb_drained_ref; void* cb_data_ref; void* self_ref; scalar_t__ fbuf_idx; scalar_t__ rbuf_idx; } ;
struct TYPE_7__ {TYPE_5__* drv; TYPE_3__ cfg; } ;
typedef  TYPE_2__ pud_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  TYPE_3__ cfg_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* init ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  empty; scalar_t__ rpos; scalar_t__ len; int /*<<< orphan*/ * data; scalar_t__ buf_size; } ;

/* Variables and functions */
 void* LUA_NOREF ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,void*) ; 
 int PCM_DRIVER_END ; 
 int PCM_DRIVER_SD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 TYPE_5__ pcm_drv_sd ; 
 int /*<<< orphan*/  sigma_delta ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int pcm_new( lua_State *L )
{
  pud_t *pud = (pud_t *) lua_newuserdata( L, sizeof( pud_t ) );
  cfg_t *cfg = &(pud->cfg);
  int driver;

  cfg->rbuf_idx = cfg->fbuf_idx = 0;
  cfg->isr_throttled = -1;  // start ISR and reader in throttled mode

  driver = luaL_checkinteger( L, 1 );
  luaL_argcheck( L, (driver >= 0) && (driver < PCM_DRIVER_END), 1, "invalid driver" );

  cfg->self_ref      = LUA_NOREF;
  cfg->cb_data_ref   = cfg->cb_drained_ref = LUA_NOREF;
  cfg->cb_paused_ref = cfg->cb_stopped_ref = LUA_NOREF;
  cfg->cb_vu_ref     = LUA_NOREF;

  cfg->bufs[0].buf_size = cfg->bufs[1].buf_size = 0;
  cfg->bufs[0].data     = cfg->bufs[1].data     = NULL;
  cfg->bufs[0].len      = cfg->bufs[1].len      = 0;
  cfg->bufs[0].rpos     = cfg->bufs[1].rpos     = 0;
  cfg->bufs[0].empty    = cfg->bufs[1].empty    = TRUE;

  cfg->vu_freq         = 10;

  if (driver == PCM_DRIVER_SD) {
    cfg->pin = luaL_checkinteger( L, 2 );
    MOD_CHECK_ID(sigma_delta, cfg->pin);

    pud->drv = &pcm_drv_sd;

    pud->drv->init( cfg );

    /* set its metatable */
    lua_pushvalue( L, -1 );  // copy self userdata to the top of stack
    luaL_getmetatable( L, "pcm.driver" );
    lua_setmetatable( L, -2 );

    return 1;
  } else {
    pud->drv = NULL;
    return 0;
  }
}