#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; char* address; } ;
typedef  TYPE_1__ memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  memCopy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 
 TYPE_1__* memReserve (int) ; 
 TYPE_1__* memString (char*) ; 
 int strlen (char*) ; 

void memStrCat(memChunk *dest, char *string) {
	memChunk result,*temp;

	temp           = memReserve (dest->size + strlen (string)+1);

	result.address = dest->address + strlen (dest->address);
	result.size    = dest->size - strlen (dest->address) + 1;

	memCopy (temp, memString (string));
	memCopy (&result, temp);

	memFree (temp);
}