#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PIMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  PE ;

/* Variables and functions */

PIMAGE_DATA_DIRECTORY pe_get_directory_entry( PE* pe, int entry) {
#if 0
	PIMAGE_DATA_DIRECTORY result = IS_64BITS_PE(pe)
		? &pe->header64->OptionalHeader.DataDirectory[entry]
		: &pe->header->OptionalHeader.DataDirectory[entry];
#else
	PIMAGE_DATA_DIRECTORY result = { 0 };
#endif
	return result;
}