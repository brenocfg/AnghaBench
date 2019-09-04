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
typedef  int /*<<< orphan*/  P_EVENT_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  g_cc3100_IRQ_handler ; 

int registerInterruptHandler(P_EVENT_HANDLER int_handler, void *pValue) {
  (void) pValue;
  g_cc3100_IRQ_handler = int_handler;
}