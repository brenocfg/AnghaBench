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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  PANDA_REV_AB ; 
 int /*<<< orphan*/  PULL_DOWN ; 
 int /*<<< orphan*/  detect_with_pull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_external_debug_serial ; 
 scalar_t__ is_entering_bootmode ; 
 scalar_t__ is_giant_panda ; 
 scalar_t__ is_grey_panda ; 
 int /*<<< orphan*/  revision ; 

void detect() {
  // detect has_external_debug_serial
  has_external_debug_serial = detect_with_pull(GPIOA, 3, PULL_DOWN);

#ifdef PANDA
  // detect is_giant_panda
  is_giant_panda = detect_with_pull(GPIOB, 1, PULL_DOWN);

  // detect panda REV C.
  // A13 floats in REV AB. In REV C, A13 is pulled up to 5V with a 10K
  // resistor and attached to the USB power control chip CTRL
  // line. Pulling A13 down with an internal 50k resistor in REV C
  // will produce a voltage divider that results in a high logic
  // level. Checking if this pin reads high with a pull down should
  // differentiate REV AB from C.
  revision = detect_with_pull(GPIOA, 13, PULL_DOWN) ? PANDA_REV_C : PANDA_REV_AB;

  // check if the ESP is trying to put me in boot mode
  is_entering_bootmode = !detect_with_pull(GPIOB, 0, PULL_UP);

  // check if it's a grey panda by seeing if the SPI lines are floating
  // TODO: is this reliable?
  is_grey_panda = !(detect_with_pull(GPIOA, 4, PULL_DOWN) | detect_with_pull(GPIOA, 5, PULL_DOWN) | detect_with_pull(GPIOA, 6, PULL_DOWN) | detect_with_pull(GPIOA, 7, PULL_DOWN));
#else
  // need to do this for early detect
  is_giant_panda = 0;
  is_grey_panda = 0;
  revision = PANDA_REV_AB;
  is_entering_bootmode = 0;
#endif
}