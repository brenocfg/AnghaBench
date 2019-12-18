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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  D0 ; 
 int /*<<< orphan*/  D1 ; 
 int /*<<< orphan*/  D2 ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 1, turn on D2 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinHigh(D2);
    } else {
        writePinLow(D2);
    }
  // if on layer 2, turn on D1 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinHigh(D1);
    } else {
        writePinLow(D1);
    }

  // if on layer 3, turn on D0 LED, otherwise off.
    if (biton32(state) == 3) {
        writePinHigh(D0);
    } else {
        writePinLow(D0);
    }

    return state;
}