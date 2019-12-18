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
struct TYPE_2__ {scalar_t__ forkNum; scalar_t__ blockNum; int /*<<< orphan*/  rnode; } ;
typedef  TYPE_1__ BufferTag ;

/* Variables and functions */
 int rnode_comparator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
buffertag_comparator(const void *a, const void *b)
{
	const BufferTag *ba = (const BufferTag *) a;
	const BufferTag *bb = (const BufferTag *) b;
	int			ret;

	ret = rnode_comparator(&ba->rnode, &bb->rnode);

	if (ret != 0)
		return ret;

	if (ba->forkNum < bb->forkNum)
		return -1;
	if (ba->forkNum > bb->forkNum)
		return 1;

	if (ba->blockNum < bb->blockNum)
		return -1;
	if (ba->blockNum > bb->blockNum)
		return 1;

	return 0;
}