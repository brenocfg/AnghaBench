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
 int /*<<< orphan*/  debug_ring ; 
 int /*<<< orphan*/  esp_ring ; 
 int /*<<< orphan*/  lin1_ring ; 
 int /*<<< orphan*/  lin2_ring ; 

uart_ring *get_ring_by_number(int a) {
  switch(a) {
    case 0:
      return &debug_ring;
    case 1:
      return &esp_ring;
    case 2:
      return &lin1_ring;
    case 3:
      return &lin2_ring;
    default:
      return NULL;
  }
}