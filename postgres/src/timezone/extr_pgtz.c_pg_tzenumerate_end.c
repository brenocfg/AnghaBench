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
struct TYPE_4__ {size_t depth; struct TYPE_4__** dirname; int /*<<< orphan*/ * dirdesc; } ;
typedef  TYPE_1__ pg_tzenum ;

/* Variables and functions */
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
pg_tzenumerate_end(pg_tzenum *dir)
{
	while (dir->depth >= 0)
	{
		FreeDir(dir->dirdesc[dir->depth]);
		pfree(dir->dirname[dir->depth]);
		dir->depth--;
	}
	pfree(dir);
}