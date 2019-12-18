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
 scalar_t__ PLVR ; 
 int /*<<< orphan*/  PV_LH ; 
 int /*<<< orphan*/  PV_LP ; 
 int /*<<< orphan*/  PV_LR ; 
 int /*<<< orphan*/  PV_O ; 
 int /*<<< orphan*/  PV_RG ; 
 int /*<<< orphan*/  PV_RL ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (scalar_t__) ; 
 int /*<<< orphan*/  layer_on (scalar_t__) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_steno(int pressed)
{
  uint8_t layer = biton32(layer_state);

  if (pressed) {
    if (layer != PLVR) layer_on(PLVR); else layer_off(PLVR);

    register_code(PV_LP);
    register_code(PV_LH);
    register_code(PV_LR);
    register_code(PV_O);
    register_code(PV_RL);
    register_code(PV_RG);
  } else {
    unregister_code(PV_LP);
    unregister_code(PV_LH);
    unregister_code(PV_LR);
    unregister_code(PV_O);
    unregister_code(PV_RL);
    unregister_code(PV_RG);
  }
}