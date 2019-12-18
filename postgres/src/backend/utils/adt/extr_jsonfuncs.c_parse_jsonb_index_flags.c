#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  root; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_1__ string; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  TYPE_4__ Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_3__*,int) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_END_ARRAY ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ jbvString ; 
 int /*<<< orphan*/  jtiAll ; 
 int /*<<< orphan*/  jtiBool ; 
 int /*<<< orphan*/  jtiKey ; 
 int /*<<< orphan*/  jtiNumeric ; 
 int /*<<< orphan*/  jtiString ; 
 scalar_t__ pg_strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pnstrdup (int /*<<< orphan*/ ,int) ; 

uint32
parse_jsonb_index_flags(Jsonb *jb)
{
	JsonbIterator *it;
	JsonbValue	v;
	JsonbIteratorToken type;
	uint32		flags = 0;

	it = JsonbIteratorInit(&jb->root);

	type = JsonbIteratorNext(&it, &v, false);

	/*
	 * We iterate over array (scalar internally is represented as array, so,
	 * we will accept it too) to check all its elements.  Flag names are
	 * chosen the same as jsonb_typeof uses.
	 */
	if (type != WJB_BEGIN_ARRAY)
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("wrong flag type, only arrays and scalars are allowed")));

	while ((type = JsonbIteratorNext(&it, &v, false)) == WJB_ELEM)
	{
		if (v.type != jbvString)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("flag array element is not a string"),
					 errhint("Possible values are: \"string\", \"numeric\", \"boolean\", \"key\", and \"all\".")));

		if (v.val.string.len == 3 &&
			pg_strncasecmp(v.val.string.val, "all", 3) == 0)
			flags |= jtiAll;
		else if (v.val.string.len == 3 &&
				 pg_strncasecmp(v.val.string.val, "key", 3) == 0)
			flags |= jtiKey;
		else if (v.val.string.len == 6 &&
				 pg_strncasecmp(v.val.string.val, "string", 5) == 0)
			flags |= jtiString;
		else if (v.val.string.len == 7 &&
				 pg_strncasecmp(v.val.string.val, "numeric", 7) == 0)
			flags |= jtiNumeric;
		else if (v.val.string.len == 7 &&
				 pg_strncasecmp(v.val.string.val, "boolean", 7) == 0)
			flags |= jtiBool;
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("wrong flag in flag array: \"%s\"",
							pnstrdup(v.val.string.val, v.val.string.len)),
					 errhint("Possible values are: \"string\", \"numeric\", \"boolean\", \"key\", and \"all\".")));
	}

	/* expect end of array now */
	if (type != WJB_END_ARRAY)
		elog(ERROR, "unexpected end of flag array");

	/* get final WJB_DONE and free iterator */
	type = JsonbIteratorNext(&it, &v, false);
	if (type != WJB_DONE)
		elog(ERROR, "unexpected end of flag array");

	return flags;
}