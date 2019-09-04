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
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MEM_STATE_OK ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mInfo ; 
 int /*<<< orphan*/  memInit () ; 
 int /*<<< orphan*/  stderr ; 

void memCheckState() {
	if (!mInfo) {
		memInit ();
	}
	if (mInfo->state != MEM_STATE_OK){
		fprintf (stderr,"\rMemory not initialized :p\n");
		exit (0);
	}
}