#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tz; int /*<<< orphan*/  typid; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {char* val; size_t len; } ;
struct TYPE_8__ {TYPE_2__ datetime; int /*<<< orphan*/  boolean; scalar_t__ numeric; TYPE_1__ string; } ;
struct TYPE_9__ {int type; TYPE_3__ val; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_4__ JsonbValue ;
typedef  int JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int JENTRY_ISBOOL_FALSE ; 
 int JENTRY_ISBOOL_TRUE ; 
 int JENTRY_ISNULL ; 
 short JENTRY_ISNUMERIC ; 
 int /*<<< orphan*/  JsonEncodeDateTime (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 int VARSIZE_ANY (scalar_t__) ; 
 int /*<<< orphan*/  appendToBuffer (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
#define  jbvBool 132 
#define  jbvDatetime 131 
#define  jbvNull 130 
#define  jbvNumeric 129 
#define  jbvString 128 
 int /*<<< orphan*/  numeric_is_nan (scalar_t__) ; 
 short padBufferToInt (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
convertJsonbScalar(StringInfo buffer, JEntry *jentry, JsonbValue *scalarVal)
{
	int			numlen;
	short		padlen;

	switch (scalarVal->type)
	{
		case jbvNull:
			*jentry = JENTRY_ISNULL;
			break;

		case jbvString:
			appendToBuffer(buffer, scalarVal->val.string.val, scalarVal->val.string.len);

			*jentry = scalarVal->val.string.len;
			break;

		case jbvNumeric:
			/* replace numeric NaN with string "NaN" */
			if (numeric_is_nan(scalarVal->val.numeric))
			{
				appendToBuffer(buffer, "NaN", 3);
				*jentry = 3;
				break;
			}

			numlen = VARSIZE_ANY(scalarVal->val.numeric);
			padlen = padBufferToInt(buffer);

			appendToBuffer(buffer, (char *) scalarVal->val.numeric, numlen);

			*jentry = JENTRY_ISNUMERIC | (padlen + numlen);
			break;

		case jbvBool:
			*jentry = (scalarVal->val.boolean) ?
				JENTRY_ISBOOL_TRUE : JENTRY_ISBOOL_FALSE;
			break;

		case jbvDatetime:
			{
				char		buf[MAXDATELEN + 1];
				size_t		len;

				JsonEncodeDateTime(buf,
								   scalarVal->val.datetime.value,
								   scalarVal->val.datetime.typid,
								   &scalarVal->val.datetime.tz);
				len = strlen(buf);
				appendToBuffer(buffer, buf, len);

				*jentry = len;
			}
			break;

		default:
			elog(ERROR, "invalid jsonb scalar type");
	}
}