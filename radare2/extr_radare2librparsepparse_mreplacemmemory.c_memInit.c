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
struct TYPE_4__ {int allocated; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ memInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_STATE_OK ; 
 TYPE_1__* mInfo ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void memInit() {
	mInfo = (memInfo*) malloc (sizeof (memInfo));
	if (!mInfo) {
		return;
	}
	memset (mInfo, 0, sizeof (memInfo));
	mInfo->state = MEM_STATE_OK;
	mInfo->allocated += sizeof (memInfo);
}