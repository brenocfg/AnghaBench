#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* address; scalar_t__ size; } ;
typedef  TYPE_1__ memChunk ;
struct TYPE_6__ {int /*<<< orphan*/  allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_3__* mInfo ; 
 int /*<<< orphan*/  memCheckState () ; 

void memFree(memChunk *chunk) {
	memCheckState ();
	if (chunk && chunk->address){
		mInfo->allocated-=chunk->size;
		free (chunk->address);
		free (chunk);
	}
}