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
 int /*<<< orphan*/  HIB_PIN ; 
 int /*<<< orphan*/  HIB_PORT ; 
 int /*<<< orphan*/  PLIB_PORTS_PinSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTS_ID_0 ; 

void CC3100_enable() {
  PLIB_PORTS_PinSet(PORTS_ID_0, HIB_PORT, HIB_PIN);
}