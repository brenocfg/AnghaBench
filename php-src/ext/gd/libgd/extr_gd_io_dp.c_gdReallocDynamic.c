#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int realSize; void* data; int /*<<< orphan*/  logicalSize; } ;
typedef  TYPE_1__ dynamicPtr ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  gdFree (void*) ; 
 void* gdMalloc (int) ; 
 void* gdRealloc (void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdReallocDynamic (dynamicPtr * dp, int required)
{
	void *newPtr;

	/* First try gdRealloc(). If that doesn't work, make a new memory block and copy. */
	if ((newPtr = gdRealloc(dp->data, required))) {
		dp->realSize = required;
		dp->data = newPtr;
		return TRUE;
	}

	/* create a new pointer */
	newPtr = gdMalloc(required);

	/* copy the old data into it */
	memcpy(newPtr, dp->data, dp->logicalSize);
	gdFree(dp->data);
	dp->data = newPtr;

	dp->realSize = required;

	return TRUE;
}