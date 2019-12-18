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
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dsmarr; } ;
typedef  TYPE_1__* ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceArrayRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ResourceOwnerForgetDSM(ResourceOwner owner, dsm_segment *seg)
{
	if (!ResourceArrayRemove(&(owner->dsmarr), PointerGetDatum(seg)))
		elog(ERROR, "dynamic shared memory segment %u is not owned by resource owner %s",
			 dsm_segment_handle(seg), owner->name);
}