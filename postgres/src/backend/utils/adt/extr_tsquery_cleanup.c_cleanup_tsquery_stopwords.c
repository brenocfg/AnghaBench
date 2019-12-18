#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_10__ {scalar_t__ type; int distance; int length; } ;
struct TYPE_9__ {scalar_t__ size; } ;
typedef  TYPE_1__* TSQuery ;
typedef  TYPE_2__ QueryOperand ;
typedef  char QueryItem ;
typedef  int /*<<< orphan*/  NODE ;

/* Variables and functions */
 int COMPUTESIZE (int,int) ; 
 char* GETOPERAND (TYPE_1__*) ; 
 char* GETQUERY (TYPE_1__*) ; 
 int HDRSIZETQ ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ QI_VAL ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int calcstrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clean_stopword_intree (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  maketree (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_1__* palloc (int) ; 
 char* plaintree (int /*<<< orphan*/ *,int*) ; 

TSQuery
cleanup_tsquery_stopwords(TSQuery in)
{
	int32		len,
				lenstr,
				commonlen,
				i;
	NODE	   *root;
	int			ladd,
				radd;
	TSQuery		out;
	QueryItem  *items;
	char	   *operands;

	if (in->size == 0)
		return in;

	/* eliminate stop words */
	root = clean_stopword_intree(maketree(GETQUERY(in)), &ladd, &radd);
	if (root == NULL)
	{
		ereport(NOTICE,
				(errmsg("text-search query contains only stop words or doesn't contain lexemes, ignored")));
		out = palloc(HDRSIZETQ);
		out->size = 0;
		SET_VARSIZE(out, HDRSIZETQ);
		return out;
	}

	/*
	 * Build TSQuery from plain view
	 */

	lenstr = calcstrlen(root);
	items = plaintree(root, &len);
	commonlen = COMPUTESIZE(len, lenstr);

	out = palloc(commonlen);
	SET_VARSIZE(out, commonlen);
	out->size = len;

	memcpy(GETQUERY(out), items, len * sizeof(QueryItem));

	items = GETQUERY(out);
	operands = GETOPERAND(out);
	for (i = 0; i < out->size; i++)
	{
		QueryOperand *op = (QueryOperand *) &items[i];

		if (op->type != QI_VAL)
			continue;

		memcpy(operands, GETOPERAND(in) + op->distance, op->length);
		operands[op->length] = '\0';
		op->distance = operands - GETOPERAND(out);
		operands += op->length + 1;
	}

	return out;
}