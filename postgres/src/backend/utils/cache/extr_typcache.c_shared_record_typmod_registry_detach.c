#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_2__ {int /*<<< orphan*/ * shared_typmod_registry; int /*<<< orphan*/ * shared_typmod_table; int /*<<< orphan*/ * shared_record_table; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_1__* CurrentSession ; 
 int /*<<< orphan*/  dshash_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shared_record_typmod_registry_detach(dsm_segment *segment, Datum datum)
{
	/* Be cautious here: maybe we didn't finish initializing. */
	if (CurrentSession->shared_record_table != NULL)
	{
		dshash_detach(CurrentSession->shared_record_table);
		CurrentSession->shared_record_table = NULL;
	}
	if (CurrentSession->shared_typmod_table != NULL)
	{
		dshash_detach(CurrentSession->shared_typmod_table);
		CurrentSession->shared_typmod_table = NULL;
	}
	CurrentSession->shared_typmod_registry = NULL;
}