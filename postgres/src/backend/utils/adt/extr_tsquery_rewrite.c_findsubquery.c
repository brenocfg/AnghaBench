#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  QTNode ;

/* Variables and functions */
 int /*<<< orphan*/ * dofindsubquery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

QTNode *
findsubquery(QTNode *root, QTNode *ex, QTNode *subs, bool *isfind)
{
	bool		DidFind = false;

	root = dofindsubquery(root, ex, subs, &DidFind);

	if (isfind)
		*isfind = DidFind;

	return root;
}