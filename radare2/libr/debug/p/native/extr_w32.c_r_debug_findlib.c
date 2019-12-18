#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {void* BaseOfDll; int /*<<< orphan*/ * hFile; } ;
typedef  TYPE_1__* PLIB_ITEM ;
typedef  int /*<<< orphan*/  LIB_ITEM ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 scalar_t__ lstLib ; 

__attribute__((used)) static void * r_debug_findlib (void * BaseOfDll) {
	PLIB_ITEM libPtr = NULL;
	if (lstLib) {
		libPtr = (PLIB_ITEM)lstLib;
		while (libPtr->hFile != NULL) {
			if (libPtr->hFile != (HANDLE)-1)
				if (libPtr->BaseOfDll == BaseOfDll)
					return ((void*)libPtr);
			libPtr = (PLIB_ITEM)((ULONG_PTR)libPtr + sizeof (LIB_ITEM));
		}
	}
	return NULL;
}