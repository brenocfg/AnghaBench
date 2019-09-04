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
typedef  int /*<<< orphan*/  PLIB_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  lstLibPtr ; 

__attribute__((used)) static  PLIB_ITEM  r_debug_get_lib_item() {
	return lstLibPtr;
}