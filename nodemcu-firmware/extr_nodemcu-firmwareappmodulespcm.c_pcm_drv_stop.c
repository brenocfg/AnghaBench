#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {TYPE_1__* drv; } ;
struct TYPE_8__ {int isr_throttled; int /*<<< orphan*/  cb_stopped_ref; int /*<<< orphan*/  self_ref; TYPE_2__* bufs; } ;
struct TYPE_7__ {int /*<<< orphan*/  empty; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* stop ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PUD () ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* cfg ; 
 int /*<<< orphan*/  dispatch_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* pud ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int pcm_drv_stop( lua_State *L )
{
  GET_PUD();

  // throttle ISR and reader
  cfg->isr_throttled = -1;

  pud->drv->stop( cfg );

  // invalidate the buffers
  cfg->bufs[0].empty = cfg->bufs[1].empty = TRUE;

  dispatch_callback( L, cfg->self_ref, cfg->cb_stopped_ref, 0 );

  return 0;
}