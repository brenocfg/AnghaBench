#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* valnode; } ;
struct TYPE_8__ {int cur; int len; int /*<<< orphan*/ * ptr; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  QueryItem ;
typedef  TYPE_2__ PLAINTREE ;
typedef  TYPE_3__ NODE ;

/* Variables and functions */
 scalar_t__ QI_OPR ; 
 scalar_t__ QI_VAL ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  plainnode (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static QueryItem *
plaintree(NODE *root, int *len)
{
	PLAINTREE	pl;

	pl.cur = 0;
	pl.len = 16;
	if (root && (root->valnode->type == QI_VAL || root->valnode->type == QI_OPR))
	{
		pl.ptr = (QueryItem *) palloc(pl.len * sizeof(QueryItem));
		plainnode(&pl, root);
	}
	else
		pl.ptr = NULL;
	*len = pl.cur;
	return pl.ptr;
}