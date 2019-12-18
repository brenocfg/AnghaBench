#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_11__ {scalar_t__ pos; scalar_t__ len; scalar_t__ haspos; } ;
typedef  TYPE_1__ WordEntry ;
struct TYPE_13__ {int ndoc; int nentry; struct TYPE_13__* right; struct TYPE_13__* left; scalar_t__ lenlexeme; int /*<<< orphan*/  lexeme; } ;
struct TYPE_12__ {int maxdepth; TYPE_3__* root; int /*<<< orphan*/  weight; } ;
typedef  TYPE_2__ TSVectorStat ;
typedef  int /*<<< orphan*/  TSVector ;
typedef  TYPE_3__ StatEntry ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 TYPE_1__* ARRPTR (int /*<<< orphan*/ ) ; 
 TYPE_3__* MemoryContextAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int POSDATALEN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ STATENTRYHDRSZ ; 
 scalar_t__ STRPTR (int /*<<< orphan*/ ) ; 
 int check_weight (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int compareStatWord (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
insertStatEntry(MemoryContext persistentContext, TSVectorStat *stat, TSVector txt, uint32 off)
{
	WordEntry  *we = ARRPTR(txt) + off;
	StatEntry  *node = stat->root,
			   *pnode = NULL;
	int			n,
				res = 0;
	uint32		depth = 1;

	if (stat->weight == 0)
		n = (we->haspos) ? POSDATALEN(txt, we) : 1;
	else
		n = (we->haspos) ? check_weight(txt, we, stat->weight) : 0;

	if (n == 0)
		return;					/* nothing to insert */

	while (node)
	{
		res = compareStatWord(node, we, txt);

		if (res == 0)
		{
			break;
		}
		else
		{
			pnode = node;
			node = (res < 0) ? node->left : node->right;
		}
		depth++;
	}

	if (depth > stat->maxdepth)
		stat->maxdepth = depth;

	if (node == NULL)
	{
		node = MemoryContextAlloc(persistentContext, STATENTRYHDRSZ + we->len);
		node->left = node->right = NULL;
		node->ndoc = 1;
		node->nentry = n;
		node->lenlexeme = we->len;
		memcpy(node->lexeme, STRPTR(txt) + we->pos, node->lenlexeme);

		if (pnode == NULL)
		{
			stat->root = node;
		}
		else
		{
			if (res < 0)
				pnode->left = node;
			else
				pnode->right = node;
		}

	}
	else
	{
		node->ndoc++;
		node->nentry += n;
	}
}