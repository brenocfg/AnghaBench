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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SYS_Initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_Tasks () ; 

int main(void) {
  /* Initialize all MPLAB Harmony modules, including application(s). */
  SYS_Initialize(NULL);

  while (1) {
    /* Maintain state machines of all polled MPLAB Harmony modules. */
    SYS_Tasks();
  }

  /* Execution should not come here during normal operation */

  return (EXIT_FAILURE);
}