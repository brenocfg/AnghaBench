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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ DVORAK_ON_BEPO ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 

int on_qwerty(){
  uint8_t deflayer = (biton32(default_layer_state));
  return (deflayer < DVORAK_ON_BEPO);
}