#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t participant; TYPE_2__* sts; int /*<<< orphan*/ * write_file; int /*<<< orphan*/ * write_chunk; } ;
struct TYPE_7__ {TYPE_1__* participants; } ;
struct TYPE_6__ {int writing; } ;
typedef  TYPE_3__ SharedTuplestoreAccessor ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sts_flush_chunk (TYPE_3__*) ; 

void
sts_end_write(SharedTuplestoreAccessor *accessor)
{
	if (accessor->write_file != NULL)
	{
		sts_flush_chunk(accessor);
		BufFileClose(accessor->write_file);
		pfree(accessor->write_chunk);
		accessor->write_chunk = NULL;
		accessor->write_file = NULL;
		accessor->sts->participants[accessor->participant].writing = false;
	}
}