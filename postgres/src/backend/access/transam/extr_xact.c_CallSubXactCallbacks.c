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
struct TYPE_3__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  SubXactEvent ;
typedef  TYPE_1__ SubXactCallbackItem ;
typedef  int /*<<< orphan*/  SubTransactionId ;

/* Variables and functions */
 TYPE_1__* SubXact_callbacks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CallSubXactCallbacks(SubXactEvent event,
					 SubTransactionId mySubid,
					 SubTransactionId parentSubid)
{
	SubXactCallbackItem *item;

	for (item = SubXact_callbacks; item; item = item->next)
		item->callback(event, mySubid, parentSubid, item->arg);
}