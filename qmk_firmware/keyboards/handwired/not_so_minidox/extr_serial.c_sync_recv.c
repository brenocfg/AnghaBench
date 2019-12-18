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
 int /*<<< orphan*/  serial_delay () ; 
 int /*<<< orphan*/  serial_input () ; 
 int /*<<< orphan*/  serial_read_pin () ; 

__attribute__((used)) static
void sync_recv(void) {
  serial_input();
  // This shouldn't hang if the slave disconnects because the
  // serial line will float to high if the slave does disconnect.
  while (!serial_read_pin());
  serial_delay();
}