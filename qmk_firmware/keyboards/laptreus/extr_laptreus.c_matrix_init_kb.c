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
 int /*<<< orphan*/  OUTPUT_AUTO ; 
 int /*<<< orphan*/  set_output (int /*<<< orphan*/ ) ; 

void matrix_init_kb() {
  // auto detect output on init
  set_output(OUTPUT_AUTO);
}