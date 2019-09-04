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

/* Variables and functions */
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  pcm_data_play ; 
 void* pcm_data_play_task ; 
 int /*<<< orphan*/  pcm_data_vu ; 
 void* pcm_data_vu_task ; 
 scalar_t__ pcm_driver_map ; 
 int /*<<< orphan*/  pcm_start_play ; 
 void* pcm_start_play_task ; 
 void* task_get_id (int /*<<< orphan*/ ) ; 

int luaopen_pcm( lua_State *L ) {
  luaL_rometatable( L, "pcm.driver", (void *)pcm_driver_map );  // create metatable

  pcm_data_vu_task    = task_get_id( pcm_data_vu );
  pcm_data_play_task  = task_get_id( pcm_data_play );
  pcm_start_play_task = task_get_id( pcm_start_play );
  return 0;
}