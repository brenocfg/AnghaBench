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
struct TYPE_4__ {struct TYPE_4__* orderByData; struct TYPE_4__* keyData; } ;
typedef  TYPE_1__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
IndexScanEnd(IndexScanDesc scan)
{
	if (scan->keyData != NULL)
		pfree(scan->keyData);
	if (scan->orderByData != NULL)
		pfree(scan->orderByData);

	pfree(scan);
}