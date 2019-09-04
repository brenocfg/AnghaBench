#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ task_param_t ;
struct TYPE_8__ {scalar_t__ isr_throttled; } ;
struct TYPE_7__ {TYPE_3__ cfg; TYPE_1__* drv; } ;
typedef  TYPE_2__ pud_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  TYPE_3__ cfg_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* play ) (TYPE_3__*) ;int /*<<< orphan*/  (* stop ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void pcm_start_play( task_param_t param, uint8 prio )
{
  lua_State *L = lua_getstate();
  pud_t *pud = (pud_t *)param;
  cfg_t *cfg = &(pud->cfg);

  // stop driver before starting it in case it hasn't been stopped from Lua
  pud->drv->stop( cfg );

  if (!pud->drv->play( cfg )) {
      luaL_error( L, "pcm driver start" );
  }

  // unthrottle ISR and reader
  pud->cfg.isr_throttled = 0;
}