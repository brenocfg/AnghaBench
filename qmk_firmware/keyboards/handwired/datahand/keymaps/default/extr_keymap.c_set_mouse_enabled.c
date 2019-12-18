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
 int mouse_enabled ; 
 int /*<<< orphan*/  set_function () ; 

__attribute__((used)) static void set_mouse_enabled(bool on) {
  mouse_enabled = on;

  /* Re-run set_function to set our layers correctly. */
  set_function();
}