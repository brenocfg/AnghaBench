#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
#define  F_NETWORK_SUB 131 
#define  F_NETWORK_SUBEQ 130 
#define  F_NETWORK_SUP 129 
#define  F_NETWORK_SUPEQ 128 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * match_network_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static List *
match_network_function(Node *leftop,
					   Node *rightop,
					   int indexarg,
					   Oid funcid,
					   Oid opfamily)
{
	switch (funcid)
	{
		case F_NETWORK_SUB:
			/* indexkey must be on the left */
			if (indexarg != 0)
				return NIL;
			return match_network_subset(leftop, rightop, false, opfamily);

		case F_NETWORK_SUBEQ:
			/* indexkey must be on the left */
			if (indexarg != 0)
				return NIL;
			return match_network_subset(leftop, rightop, true, opfamily);

		case F_NETWORK_SUP:
			/* indexkey must be on the right */
			if (indexarg != 1)
				return NIL;
			return match_network_subset(rightop, leftop, false, opfamily);

		case F_NETWORK_SUPEQ:
			/* indexkey must be on the right */
			if (indexarg != 1)
				return NIL;
			return match_network_subset(rightop, leftop, true, opfamily);

		default:

			/*
			 * We'd only get here if somebody attached this support function
			 * to an unexpected function.  Maybe we should complain, but for
			 * now, do nothing.
			 */
			return NIL;
	}
}