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
struct TYPE_3__ {int* changed; char** values; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepTupleData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pq_copymsgbytes (int /*<<< orphan*/ ,char*,int) ; 
 char pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int pq_getmsgint (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
logicalrep_read_tuple(StringInfo in, LogicalRepTupleData *tuple)
{
	int			i;
	int			natts;

	/* Get number of attributes */
	natts = pq_getmsgint(in, 2);

	memset(tuple->changed, 0, sizeof(tuple->changed));

	/* Read the data */
	for (i = 0; i < natts; i++)
	{
		char		kind;

		kind = pq_getmsgbyte(in);

		switch (kind)
		{
			case 'n':			/* null */
				tuple->values[i] = NULL;
				tuple->changed[i] = true;
				break;
			case 'u':			/* unchanged column */
				/* we don't receive the value of an unchanged column */
				tuple->values[i] = NULL;
				break;
			case 't':			/* text formatted value */
				{
					int			len;

					tuple->changed[i] = true;

					len = pq_getmsgint(in, 4);	/* read length */

					/* and data */
					tuple->values[i] = palloc(len + 1);
					pq_copymsgbytes(in, tuple->values[i], len);
					tuple->values[i][len] = '\0';
				}
				break;
			default:
				elog(ERROR, "unrecognized data representation type '%c'", kind);
		}
	}
}