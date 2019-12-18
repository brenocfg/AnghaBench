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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  QueryItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  findoprnd_recurse (int /*<<< orphan*/ *,int*,int,int*) ; 

__attribute__((used)) static void
findoprnd(QueryItem *ptr, int size, bool *needcleanup)
{
	uint32		pos;

	*needcleanup = false;
	pos = 0;
	findoprnd_recurse(ptr, &pos, size, needcleanup);

	if (pos != size)
		elog(ERROR, "malformed tsquery: extra nodes");
}