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
 scalar_t__ handle ; 

__attribute__((used)) static int fini(void *p) {
	if (handle != 0) {
		// SEGFAULTS RANDOMLY, better leak on exit
		// cs_close (&handle);
		handle = 0;
	}
	return true;
}