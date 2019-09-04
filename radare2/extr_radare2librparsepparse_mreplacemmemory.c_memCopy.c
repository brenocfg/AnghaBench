#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long size; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  memCheckState () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

void memCopy(memChunk *dest,memChunk *source) {
	long nbytes;
	memCheckState ();
	if ((!source->address) || (!dest->address)) {
		return;
	}
	nbytes=dest->size > source->size ? source->size : dest->size;
	#if DEBUG3
	eprintf ("Copying %d byte(s) to dest (size %d)\n", nbytes, dest->address, dest->size);
	#endif
	memcpy (dest->address, source->address, nbytes);
}