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
struct TYPE_3__ {int logpageno; int level; } ;
typedef  TYPE_1__ FSMAddress ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int FSM_TREE_DEPTH ; 
 int SlotsPerFSMPage ; 

__attribute__((used)) static BlockNumber
fsm_logical_to_physical(FSMAddress addr)
{
	BlockNumber pages;
	int			leafno;
	int			l;

	/*
	 * Calculate the logical page number of the first leaf page below the
	 * given page.
	 */
	leafno = addr.logpageno;
	for (l = 0; l < addr.level; l++)
		leafno *= SlotsPerFSMPage;

	/* Count upper level nodes required to address the leaf page */
	pages = 0;
	for (l = 0; l < FSM_TREE_DEPTH; l++)
	{
		pages += leafno + 1;
		leafno /= SlotsPerFSMPage;
	}

	/*
	 * If the page we were asked for wasn't at the bottom level, subtract the
	 * additional lower level pages we counted above.
	 */
	pages -= addr.level;

	/* Turn the page count into 0-based block number */
	return pages - 1;
}