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
struct TYPE_3__ {scalar_t__ index_tuples; scalar_t__ heap_tuples; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  TYPE_1__ IndexBuildResult ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static IndexBuildResult *
dibuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;

	result = (IndexBuildResult *) palloc(sizeof(IndexBuildResult));

	/* let's pretend that no tuples were scanned */
	result->heap_tuples = 0;
	/* and no index tuples were created (that is true) */
	result->index_tuples = 0;

	return result;
}