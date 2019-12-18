#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__* TSQuery ;
typedef  int /*<<< orphan*/  QTNode ;

/* Variables and functions */
 int /*<<< orphan*/  GETOPERAND (TYPE_1__*) ; 
 int /*<<< orphan*/  GETQUERY (TYPE_1__*) ; 
 int /*<<< orphan*/ * QT2QTN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QTNFree (int /*<<< orphan*/ *) ; 
 int QTNodeCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ VARSIZE (TYPE_1__*) ; 

__attribute__((used)) static int
CompareTSQ(TSQuery a, TSQuery b)
{
	if (a->size != b->size)
	{
		return (a->size < b->size) ? -1 : 1;
	}
	else if (VARSIZE(a) != VARSIZE(b))
	{
		return (VARSIZE(a) < VARSIZE(b)) ? -1 : 1;
	}
	else if (a->size != 0)
	{
		QTNode	   *an = QT2QTN(GETQUERY(a), GETOPERAND(a));
		QTNode	   *bn = QT2QTN(GETQUERY(b), GETOPERAND(b));
		int			res = QTNodeCompare(an, bn);

		QTNFree(an);
		QTNFree(bn);

		return res;
	}

	return 0;
}