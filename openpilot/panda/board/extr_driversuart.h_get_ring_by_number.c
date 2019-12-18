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
typedef  int /*<<< orphan*/  uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  uart_ring_debug ; 
 int /*<<< orphan*/  uart_ring_esp_gps ; 
 int /*<<< orphan*/  uart_ring_lin1 ; 
 int /*<<< orphan*/  uart_ring_lin2 ; 

uart_ring *get_ring_by_number(int a) {
  uart_ring *ring = NULL;
  switch(a) {
    case 0:
      ring = &uart_ring_debug;
      break;
    case 1:
      ring = &uart_ring_esp_gps;
      break;
    case 2:
      ring = &uart_ring_lin1;
      break;
    case 3:
      ring = &uart_ring_lin2;
      break;
    default:
      ring = NULL;
      break;
  }
  return ring;
}