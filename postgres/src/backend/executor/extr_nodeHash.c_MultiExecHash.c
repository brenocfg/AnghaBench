#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ instrument; } ;
struct TYPE_9__ {TYPE_2__* hashtable; TYPE_1__ ps; int /*<<< orphan*/ * parallel_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  partialTuples; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ HashState ;

/* Variables and functions */
 int /*<<< orphan*/  InstrStartNode (scalar_t__) ; 
 int /*<<< orphan*/  InstrStopNode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiExecParallelHash (TYPE_3__*) ; 
 int /*<<< orphan*/  MultiExecPrivateHash (TYPE_3__*) ; 

Node *
MultiExecHash(HashState *node)
{
	/* must provide our own instrumentation support */
	if (node->ps.instrument)
		InstrStartNode(node->ps.instrument);

	if (node->parallel_state != NULL)
		MultiExecParallelHash(node);
	else
		MultiExecPrivateHash(node);

	/* must provide our own instrumentation support */
	if (node->ps.instrument)
		InstrStopNode(node->ps.instrument, node->hashtable->partialTuples);

	/*
	 * We do not return the hash table directly because it's not a subtype of
	 * Node, and so would violate the MultiExecProcNode API.  Instead, our
	 * parent Hashjoin node is expected to know how to fish it out of our node
	 * state.  Ugly but not really worth cleaning up, since Hashjoin knows
	 * quite a bit more about Hash besides that.
	 */
	return NULL;
}