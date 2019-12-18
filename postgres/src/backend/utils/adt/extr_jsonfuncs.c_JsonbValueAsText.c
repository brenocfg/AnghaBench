#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {char* val; int len; } ;
struct TYPE_11__ {TYPE_2__ binary; int /*<<< orphan*/  numeric; TYPE_1__ string; int /*<<< orphan*/  boolean; } ;
struct TYPE_13__ {int type; TYPE_3__ val; } ;
struct TYPE_12__ {char* data; int len; } ;
typedef  TYPE_4__ StringInfoData ;
typedef  TYPE_5__ JsonbValue ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JsonbToCString (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstring_to_text_with_len (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_4__*) ; 
#define  jbvBinary 132 
#define  jbvBool 131 
#define  jbvNull 130 
#define  jbvNumeric 129 
#define  jbvString 128 
 int /*<<< orphan*/  numeric_out ; 

__attribute__((used)) static text *
JsonbValueAsText(JsonbValue *v)
{
	switch (v->type)
	{
		case jbvNull:
			return NULL;

		case jbvBool:
			return v->val.boolean ?
				cstring_to_text_with_len("true", 4) :
				cstring_to_text_with_len("false", 5);

		case jbvString:
			return cstring_to_text_with_len(v->val.string.val,
											v->val.string.len);

		case jbvNumeric:
			{
				Datum		cstr;

				cstr = DirectFunctionCall1(numeric_out,
										   PointerGetDatum(v->val.numeric));

				return cstring_to_text(DatumGetCString(cstr));
			}

		case jbvBinary:
			{
				StringInfoData jtext;

				initStringInfo(&jtext);
				(void) JsonbToCString(&jtext, v->val.binary.data,
									  v->val.binary.len);

				return cstring_to_text_with_len(jtext.data, jtext.len);
			}

		default:
			elog(ERROR, "unrecognized jsonb type: %d", (int) v->type);
			return NULL;
	}
}