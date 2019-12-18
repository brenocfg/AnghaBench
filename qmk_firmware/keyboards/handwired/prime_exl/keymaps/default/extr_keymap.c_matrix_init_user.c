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
 int /*<<< orphan*/  B5 ; 
 int /*<<< orphan*/  B6 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(C6);
  writePinHigh(C6);
  // set NumLock LED to output and low
  setPinOutput(B6);
  writePinHigh(B6);
  // set ScrollLock LED to output and low
  setPinOutput(B5);
  writePinHigh(B5);
}