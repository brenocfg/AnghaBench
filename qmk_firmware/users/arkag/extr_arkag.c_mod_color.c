#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int h; } ;
typedef  TYPE_1__ Color ;

/* Variables and functions */
 int /*<<< orphan*/  save_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  underglow ; 

Color mod_color(Color current_color, bool should_add, uint8_t change_amount) {
  save_color(underglow);
  int addlim = 359 - change_amount;
  int sublim = change_amount;
  int leftovers;
  if (should_add) {
    if (current_color.h <= addlim) {
      current_color.h += change_amount;
    } else {
      leftovers = (359 + change_amount) % 359;
      current_color.h  = 0 + leftovers;
    }
  } else {
    if (current_color.h >= sublim) {
      current_color.h -= change_amount;
    } else {
      leftovers = change_amount - current_color.h;
      current_color.h  = 359 - leftovers;
    }
  }
  return current_color;
}