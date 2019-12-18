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
typedef  int uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  root; } ;
struct TYPE_7__ {char* val; int len; } ;
struct TYPE_8__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  numeric; TYPE_1__ string; } ;
struct TYPE_9__ {int type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  TYPE_4__ Jsonb ;
typedef  int /*<<< orphan*/  (* JsonIterateStringValuesAction ) (void*,char*,int) ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_3__*,int) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_KEY ; 
 scalar_t__ WJB_VALUE ; 
#define  jbvBool 130 
#define  jbvNumeric 129 
#define  jbvString 128 
 int jtiBool ; 
 int jtiKey ; 
 int jtiNumeric ; 
 int jtiString ; 
 int /*<<< orphan*/  numeric_out ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int strlen (char*) ; 

void
iterate_jsonb_values(Jsonb *jb, uint32 flags, void *state,
					 JsonIterateStringValuesAction action)
{
	JsonbIterator *it;
	JsonbValue	v;
	JsonbIteratorToken type;

	it = JsonbIteratorInit(&jb->root);

	/*
	 * Just recursively iterating over jsonb and call callback on all
	 * corresponding elements
	 */
	while ((type = JsonbIteratorNext(&it, &v, false)) != WJB_DONE)
	{
		if (type == WJB_KEY)
		{
			if (flags & jtiKey)
				action(state, v.val.string.val, v.val.string.len);

			continue;
		}
		else if (!(type == WJB_VALUE || type == WJB_ELEM))
		{
			/* do not call callback for composite JsonbValue */
			continue;
		}

		/* JsonbValue is a value of object or element of array */
		switch (v.type)
		{
			case jbvString:
				if (flags & jtiString)
					action(state, v.val.string.val, v.val.string.len);
				break;
			case jbvNumeric:
				if (flags & jtiNumeric)
				{
					char	   *val;

					val = DatumGetCString(DirectFunctionCall1(numeric_out,
															  NumericGetDatum(v.val.numeric)));

					action(state, val, strlen(val));
					pfree(val);
				}
				break;
			case jbvBool:
				if (flags & jtiBool)
				{
					if (v.val.boolean)
						action(state, "true", 4);
					else
						action(state, "false", 5);
				}
				break;
			default:
				/* do not call callback for composite JsonbValue */
				break;
		}
	}
}