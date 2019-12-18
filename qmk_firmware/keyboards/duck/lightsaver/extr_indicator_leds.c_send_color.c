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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum Device { ____Placeholder_Device } Device ;

/* Variables and functions */
 int /*<<< orphan*/  send_value (int /*<<< orphan*/ ,int) ; 

void send_color(uint8_t r, uint8_t g, uint8_t b, enum Device device) {
  send_value(r, device);
  send_value(g, device);
  send_value(b, device);
}