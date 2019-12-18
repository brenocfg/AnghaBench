#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ relid; } ;
struct TYPE_4__ {scalar_t__ localreloid; scalar_t__ state; scalar_t__ statelsn; } ;
typedef  TYPE_1__ LogicalRepRelMapEntry ;

/* Variables and functions */
 TYPE_3__* MyLogicalRepWorker ; 
 scalar_t__ SUBREL_STATE_READY ; 
 scalar_t__ SUBREL_STATE_SYNCDONE ; 
 scalar_t__ am_tablesync_worker () ; 
 scalar_t__ remote_final_lsn ; 

__attribute__((used)) static bool
should_apply_changes_for_rel(LogicalRepRelMapEntry *rel)
{
	if (am_tablesync_worker())
		return MyLogicalRepWorker->relid == rel->localreloid;
	else
		return (rel->state == SUBREL_STATE_READY ||
				(rel->state == SUBREL_STATE_SYNCDONE &&
				 rel->statelsn <= remote_final_lsn));
}