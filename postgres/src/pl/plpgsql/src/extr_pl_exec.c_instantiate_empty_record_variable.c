#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  datum_context; } ;
struct TYPE_6__ {scalar_t__ rectypeid; int /*<<< orphan*/ * erh; int /*<<< orphan*/  refname; } ;
typedef  TYPE_1__ PLpgSQL_rec ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_expanded_record_from_typeid (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_rectypeid (TYPE_1__*) ; 

__attribute__((used)) static void
instantiate_empty_record_variable(PLpgSQL_execstate *estate, PLpgSQL_rec *rec)
{
	Assert(rec->erh == NULL);	/* else caller error */

	/* If declared type is RECORD, we can't instantiate */
	if (rec->rectypeid == RECORDOID)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("record \"%s\" is not assigned yet", rec->refname),
				 errdetail("The tuple structure of a not-yet-assigned record is indeterminate.")));

	/* Make sure rec->rectypeid is up-to-date before using it */
	revalidate_rectypeid(rec);

	/* OK, do it */
	rec->erh = make_expanded_record_from_typeid(rec->rectypeid, -1,
												estate->datum_context);
}