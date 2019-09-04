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
typedef  int /*<<< orphan*/  memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  memCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memReserve (long) ; 
 int /*<<< orphan*/  memString (char*) ; 

memChunk *memStringReserve(char *string, long nbytes) {
	static memChunk *buffer;
	buffer=memReserve (nbytes);
	memCopy (buffer, memString (string));
	return buffer;
}