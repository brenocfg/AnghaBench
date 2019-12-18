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

/* Variables and functions */
 scalar_t__ tetris_running ; 
 int /*<<< orphan*/  tetris_tick (int) ; 
 int tetris_timer ; 

void matrix_scan_user(void) {
  if (tetris_running) {
    tetris_timer++;
    if (tetris_timer > 1000) {
      // every 1000 times this is run is about 100 ms.
      if (!tetris_tick(100)) {
        // game over
        tetris_running = 0;
      }
      tetris_timer = 0;
    }
  }      
}