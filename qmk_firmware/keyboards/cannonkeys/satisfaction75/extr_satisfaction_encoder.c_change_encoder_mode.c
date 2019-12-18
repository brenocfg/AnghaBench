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
 int _NUM_ENCODER_MODES ; 
 int enabled_encoder_modes ; 
 int encoder_mode ; 
 int /*<<< orphan*/  post_encoder_mode_change () ; 
 int /*<<< orphan*/  pre_encoder_mode_change () ; 

void change_encoder_mode(bool negative){
  pre_encoder_mode_change();
  if(enabled_encoder_modes == 0){
    enabled_encoder_modes = 0x1F;
  }
  do {
    if(negative){
      if (encoder_mode == 0){
        encoder_mode = _NUM_ENCODER_MODES - 1;
      } else{
        encoder_mode = encoder_mode - 1;
      }
    } else {
        encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
    }
  } while(((1 << encoder_mode) & enabled_encoder_modes) == 0);
  post_encoder_mode_change();
}