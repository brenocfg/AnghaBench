#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* address; long size; } ;
typedef  TYPE_1__ memChunk ;
struct TYPE_5__ {long allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_3__* mInfo ; 
 scalar_t__ malloc (long) ; 
 int /*<<< orphan*/  memCheckState () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  perror (char*) ; 

memChunk *memReserve(long size) {
	static memChunk *buffer;
	memCheckState ();
	buffer = (memChunk*)malloc (sizeof (memChunk));
	if (!buffer || !(buffer->address = (char*)malloc (size))) {
		perror ("memReserve");
		exit (0);
  	}
	//printf("- reservando %d byte(s)\n",size);
	buffer->size = size;
	memset (buffer->address, 0, buffer->size);
	mInfo->allocated += buffer->size;
	return buffer;
}