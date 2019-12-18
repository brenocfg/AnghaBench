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
struct TYPE_3__ {int allocated; scalar_t__ count; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ GinEntries ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * palloc (int) ; 

__attribute__((used)) static void
init_gin_entries(GinEntries *entries, int preallocated)
{
	entries->allocated = preallocated;
	entries->buf = preallocated ? palloc(sizeof(Datum) * preallocated) : NULL;
	entries->count = 0;
}