#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* pages; TYPE_2__* images; int /*<<< orphan*/  isLogged; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  image; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_3__ GenericXLogState ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBuffer ; 
 int MAX_GENERIC_XLOG_PAGES ; 
 int /*<<< orphan*/  RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

GenericXLogState *
GenericXLogStart(Relation relation)
{
	GenericXLogState *state;
	int			i;

	state = (GenericXLogState *) palloc(sizeof(GenericXLogState));
	state->isLogged = RelationNeedsWAL(relation);

	for (i = 0; i < MAX_GENERIC_XLOG_PAGES; i++)
	{
		state->pages[i].image = state->images[i].data;
		state->pages[i].buffer = InvalidBuffer;
	}

	return state;
}