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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void long_keystroke(size_t num_of_keys, uint16_t keys[]) {
  for (int i = 0; i < num_of_keys-1; i++) {
    register_code(keys[i]);
  }
  tap_code(keys[num_of_keys-1]);
  for (int i = 0; i < num_of_keys-1; i++) {
    unregister_code(keys[i]);
  }
}