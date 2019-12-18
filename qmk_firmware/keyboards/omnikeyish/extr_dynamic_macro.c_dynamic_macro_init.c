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
typedef  int /*<<< orphan*/  dynamic_macro_t ;

/* Variables and functions */
 int DYNAMIC_MACRO_COUNT ; 
 int /*<<< orphan*/  dynamic_macros ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void dynamic_macro_init(void) {
  /* zero out macro blocks  */
  memset(&dynamic_macros, 0, DYNAMIC_MACRO_COUNT * sizeof(dynamic_macro_t));
}