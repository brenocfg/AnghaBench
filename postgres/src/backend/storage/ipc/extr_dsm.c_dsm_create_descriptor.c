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
struct TYPE_5__ {int /*<<< orphan*/  on_detach; scalar_t__ resowner; scalar_t__ mapped_size; int /*<<< orphan*/ * mapped_address; int /*<<< orphan*/ * impl_private; int /*<<< orphan*/  control_slot; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ dsm_segment ;

/* Variables and functions */
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  INVALID_CONTROL_SLOT ; 
 TYPE_1__* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeDSMs (scalar_t__) ; 
 int /*<<< orphan*/  ResourceOwnerRememberDSM (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_list ; 
 int /*<<< orphan*/  slist_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dsm_segment *
dsm_create_descriptor(void)
{
	dsm_segment *seg;

	if (CurrentResourceOwner)
		ResourceOwnerEnlargeDSMs(CurrentResourceOwner);

	seg = MemoryContextAlloc(TopMemoryContext, sizeof(dsm_segment));
	dlist_push_head(&dsm_segment_list, &seg->node);

	/* seg->handle must be initialized by the caller */
	seg->control_slot = INVALID_CONTROL_SLOT;
	seg->impl_private = NULL;
	seg->mapped_address = NULL;
	seg->mapped_size = 0;

	seg->resowner = CurrentResourceOwner;
	if (CurrentResourceOwner)
		ResourceOwnerRememberDSM(CurrentResourceOwner, seg);

	slist_init(&seg->on_detach);

	return seg;
}