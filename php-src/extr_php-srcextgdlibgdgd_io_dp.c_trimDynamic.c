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
struct TYPE_4__ {int /*<<< orphan*/  logicalSize; int /*<<< orphan*/  freeOK; } ;
typedef  TYPE_1__ dynamicPtr ;

/* Variables and functions */
 int FALSE ; 
 int gdReallocDynamic (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trimDynamic (dynamicPtr * dp)
{
	/* 2.0.21: we don't reallocate memory we don't own */
	if (!dp->freeOK) {
		return FALSE;
	}
	return gdReallocDynamic(dp, dp->logicalSize);
}