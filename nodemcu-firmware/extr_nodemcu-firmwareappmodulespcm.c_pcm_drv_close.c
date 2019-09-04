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
struct TYPE_4__ {TYPE_1__* drv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PUD () ; 
 int /*<<< orphan*/  cfg ; 
 int pcm_drv_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* pud ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_drv_close( lua_State *L )
{
  GET_PUD();

  pud->drv->close( cfg );

  return pcm_drv_free( L );
}