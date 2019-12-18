#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_1__ DumpableObject ;

/* Variables and functions */
 int /*<<< orphan*/  removeObjectDependency (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repairIndexLoop(DumpableObject *partedindex,
				DumpableObject *partindex)
{
	removeObjectDependency(partedindex, partindex->dumpId);
}