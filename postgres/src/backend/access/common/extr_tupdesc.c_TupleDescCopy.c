#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_11__ {int attnotnull; int atthasdef; int atthasmissing; char attidentity; char attgenerated; } ;
struct TYPE_10__ {int natts; int tdrefcount; int /*<<< orphan*/ * constr; } ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TupleDescSize (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
TupleDescCopy(TupleDesc dst, TupleDesc src)
{
	int			i;

	/* Flat-copy the header and attribute array */
	memcpy(dst, src, TupleDescSize(src));

	/*
	 * Since we're not copying constraints and defaults, clear fields
	 * associated with them.
	 */
	for (i = 0; i < dst->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(dst, i);

		att->attnotnull = false;
		att->atthasdef = false;
		att->atthasmissing = false;
		att->attidentity = '\0';
		att->attgenerated = '\0';
	}
	dst->constr = NULL;

	/*
	 * Also, assume the destination is not to be ref-counted.  (Copying the
	 * source's refcount would be wrong in any case.)
	 */
	dst->tdrefcount = -1;
}