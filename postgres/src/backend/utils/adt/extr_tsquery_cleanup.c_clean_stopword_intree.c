#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* valnode; struct TYPE_10__* left; struct TYPE_10__* right; } ;
struct TYPE_8__ {scalar_t__ oper; int distance; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  TYPE_3__ NODE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int Max (int,int) ; 
 scalar_t__ OP_NOT ; 
 scalar_t__ OP_PHRASE ; 
 scalar_t__ QI_OPR ; 
 scalar_t__ QI_VAL ; 
 scalar_t__ QI_VALSTOP ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  freetree (TYPE_3__*) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static NODE *
clean_stopword_intree(NODE *node, int *ladd, int *radd)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	/* default output parameters indicate no change in parent distance */
	*ladd = *radd = 0;

	if (node->valnode->type == QI_VAL)
		return node;
	else if (node->valnode->type == QI_VALSTOP)
	{
		pfree(node);
		return NULL;
	}

	Assert(node->valnode->type == QI_OPR);

	if (node->valnode->qoperator.oper == OP_NOT)
	{
		/* NOT doesn't change pattern width, so just report child distances */
		node->right = clean_stopword_intree(node->right, ladd, radd);
		if (!node->right)
		{
			freetree(node);
			return NULL;
		}
	}
	else
	{
		NODE	   *res = node;
		bool		isphrase;
		int			ndistance,
					lladd,
					lradd,
					rladd,
					rradd;

		/* First, recurse */
		node->left = clean_stopword_intree(node->left, &lladd, &lradd);
		node->right = clean_stopword_intree(node->right, &rladd, &rradd);

		/* Check if current node is OP_PHRASE, get its distance */
		isphrase = (node->valnode->qoperator.oper == OP_PHRASE);
		ndistance = isphrase ? node->valnode->qoperator.distance : 0;

		if (node->left == NULL && node->right == NULL)
		{
			/*
			 * When we collapse out a phrase node entirely, propagate its own
			 * distance into both *ladd and *radd; it is the responsibility of
			 * the parent node to count it only once.  Also, for a phrase
			 * node, distances coming from children are summed and propagated
			 * up to parent (we assume lladd == lradd and rladd == rradd, else
			 * rule was broken at a lower level).  But if this isn't a phrase
			 * node, take the larger of the two child distances; that
			 * corresponds to what TS_execute will do in non-stopword cases.
			 */
			if (isphrase)
				*ladd = *radd = lladd + ndistance + rladd;
			else
				*ladd = *radd = Max(lladd, rladd);
			freetree(node);
			return NULL;
		}
		else if (node->left == NULL)
		{
			/* Removing this operator and left subnode */
			/* lladd and lradd are equal/redundant, don't count both */
			if (isphrase)
			{
				/* operator's own distance must propagate to left */
				*ladd = lladd + ndistance + rladd;
				*radd = rradd;
			}
			else
			{
				/* at non-phrase op, just forget the left subnode entirely */
				*ladd = rladd;
				*radd = rradd;
			}
			res = node->right;
			pfree(node);
		}
		else if (node->right == NULL)
		{
			/* Removing this operator and right subnode */
			/* rladd and rradd are equal/redundant, don't count both */
			if (isphrase)
			{
				/* operator's own distance must propagate to right */
				*ladd = lladd;
				*radd = lradd + ndistance + rradd;
			}
			else
			{
				/* at non-phrase op, just forget the right subnode entirely */
				*ladd = lladd;
				*radd = lradd;
			}
			res = node->left;
			pfree(node);
		}
		else if (isphrase)
		{
			/* Absorb appropriate corrections at this level */
			node->valnode->qoperator.distance += lradd + rladd;
			/* Propagate up any unaccounted-for corrections */
			*ladd = lladd;
			*radd = rradd;
		}
		else
		{
			/* We're keeping a non-phrase operator, so ladd/radd remain 0 */
		}

		return res;
	}
	return node;
}