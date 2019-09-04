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
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  memCheckState () ; 
 TYPE_1__* memReserve (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

memChunk *memString(char *string) {
	static memChunk *buffer;
	memCheckState ();
	buffer = memReserve (strlen (string) + 1);
	memcpy (buffer->address, string, strlen (string));
	return buffer;
}