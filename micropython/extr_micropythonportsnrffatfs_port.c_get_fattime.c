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
typedef  int DWORD ;

/* Variables and functions */

DWORD get_fattime(void) {
	// TODO: Implement this function. For now, fake it.
    return ((2016 - 1980) << 25) | ((12) << 21) | ((4) << 16) | ((00) << 11) | ((18) << 5) | (23 / 2);
}