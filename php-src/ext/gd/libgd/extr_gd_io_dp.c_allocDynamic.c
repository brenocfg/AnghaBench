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
struct TYPE_3__ {int logicalSize; int dataGood; int realSize; scalar_t__ pos; void* data; } ;
typedef  TYPE_1__ dynamicPtr ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 void* gdMalloc (int) ; 

__attribute__((used)) static int
allocDynamic (dynamicPtr * dp, int initialSize, void *data)
{

	if (data == NULL) {
		dp->logicalSize = 0;
		dp->dataGood = FALSE;
		dp->data = gdMalloc(initialSize);
	} else {
		dp->logicalSize = initialSize;
		dp->dataGood = TRUE;
		dp->data = data;
	}

	dp->realSize = initialSize;
	dp->dataGood = TRUE;
	dp->pos = 0;

	return TRUE;
}