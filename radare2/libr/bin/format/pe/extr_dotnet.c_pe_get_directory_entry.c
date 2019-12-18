#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* header; TYPE_2__* header64; } ;
struct TYPE_12__ {int /*<<< orphan*/ * DataDirectory; } ;
struct TYPE_13__ {TYPE_4__ OptionalHeader; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/ * DataDirectory; } ;
struct TYPE_10__ {TYPE_1__ OptionalHeader; } ;
typedef  int /*<<< orphan*/ * PIMAGE_DATA_DIRECTORY ;
typedef  TYPE_6__ PE ;

/* Variables and functions */
 scalar_t__ IS_64BITS_PE (TYPE_6__*) ; 

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