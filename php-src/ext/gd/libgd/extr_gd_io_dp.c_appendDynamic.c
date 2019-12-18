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
struct TYPE_4__ {int pos; int realSize; int logicalSize; scalar_t__ data; int /*<<< orphan*/  freeOK; int /*<<< orphan*/  dataGood; } ;
typedef  TYPE_1__ dynamicPtr ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  gdReallocDynamic (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__attribute__((used)) static int appendDynamic (dynamicPtr * dp, const void *src, int size)
{
	int bytesNeeded;
	char *tmp;

	if (!dp->dataGood) {
		return FALSE;
	}

	/*  bytesNeeded = dp->logicalSize + size; */
	bytesNeeded = dp->pos + size;

	if (bytesNeeded > dp->realSize) {
		/* 2.0.21 */
		if (!dp->freeOK) {
			return FALSE;
		}
		gdReallocDynamic(dp, bytesNeeded * 2);
	}

	/* if we get here, we can be sure that we have enough bytes to copy safely */
	/*printf("Mem OK Size: %d, Pos: %d\n", dp->realSize, dp->pos); */

	tmp = (char *) dp->data;
	memcpy((void *) (tmp + (dp->pos)), src, size);
	dp->pos += size;

	if (dp->pos > dp->logicalSize) {
		dp->logicalSize = dp->pos;
	}

	return TRUE;
}