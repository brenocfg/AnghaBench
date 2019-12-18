#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_mappings; } ;
struct TYPE_7__ {scalar_t__ num_mappings; } ;
struct TYPE_6__ {scalar_t__ num_mappings; } ;
struct TYPE_5__ {scalar_t__ num_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_4__ active_local_updates ; 
 TYPE_3__ active_shared_updates ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_2__ pending_local_updates ; 
 TYPE_1__ pending_shared_updates ; 

void
AtPrepare_RelationMap(void)
{
	if (active_shared_updates.num_mappings != 0 ||
		active_local_updates.num_mappings != 0 ||
		pending_shared_updates.num_mappings != 0 ||
		pending_local_updates.num_mappings != 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot PREPARE a transaction that modified relation mapping")));
}