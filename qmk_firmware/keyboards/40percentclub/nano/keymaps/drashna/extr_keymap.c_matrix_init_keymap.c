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
 void* analogRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swPin ; 
 void* xOrigin ; 
 int /*<<< orphan*/  xPin ; 
 void* yOrigin ; 
 int /*<<< orphan*/  yPin ; 

void matrix_init_keymap(void) {
    // init pin? Is needed?
    setPinInputHigh(swPin);
    // Account for drift
    xOrigin = analogRead(xPin);
    yOrigin = analogRead(yPin);
}