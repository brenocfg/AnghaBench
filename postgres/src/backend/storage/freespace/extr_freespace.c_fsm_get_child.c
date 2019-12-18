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
typedef  int uint16 ;
struct TYPE_4__ {scalar_t__ level; int logpageno; } ;
typedef  TYPE_1__ FSMAddress ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FSM_BOTTOM_LEVEL ; 
 int SlotsPerFSMPage ; 

__attribute__((used)) static FSMAddress
fsm_get_child(FSMAddress parent, uint16 slot)
{
	FSMAddress	child;

	Assert(parent.level > FSM_BOTTOM_LEVEL);

	child.level = parent.level - 1;
	child.logpageno = parent.logpageno * SlotsPerFSMPage + slot;

	return child;
}