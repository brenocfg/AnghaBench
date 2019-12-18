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
struct TYPE_4__ {int /*<<< orphan*/ * resowner; } ;
typedef  TYPE_1__ dsm_segment ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeDSMs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceOwnerRememberDSM (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
dsm_unpin_mapping(dsm_segment *seg)
{
	Assert(seg->resowner == NULL);
	ResourceOwnerEnlargeDSMs(CurrentResourceOwner);
	seg->resowner = CurrentResourceOwner;
	ResourceOwnerRememberDSM(seg->resowner, seg);
}