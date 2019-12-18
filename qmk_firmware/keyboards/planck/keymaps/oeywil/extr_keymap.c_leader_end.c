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
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defsong ; 
 int /*<<< orphan*/  failed ; 
 int /*<<< orphan*/  gamesong ; 
 scalar_t__ leader_layer_def ; 
 scalar_t__ leader_layer_game ; 
 scalar_t__ leader_succeed ; 

void leader_end(void) {
  if (leader_succeed) {
    // do nothing
  } else if (leader_layer_game) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(gamesong);
    #endif
  } else if (leader_layer_def) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(defsong);
    #endif
  } else {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(failed);
    #endif
  }
}