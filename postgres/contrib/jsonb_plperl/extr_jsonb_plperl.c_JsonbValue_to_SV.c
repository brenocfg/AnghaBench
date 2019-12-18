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
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  boolean; TYPE_1__ string; int /*<<< orphan*/  numeric; TYPE_2__ binary; } ;
struct TYPE_9__ {int type; TYPE_3__ val; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_4__ JsonbValue ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * Jsonb_to_SV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_sv_no ; 
 int /*<<< orphan*/  PL_sv_yes ; 
 int /*<<< orphan*/  SvNV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstr2sv (char*) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
#define  jbvBinary 132 
#define  jbvBool 131 
#define  jbvNull 130 
#define  jbvNumeric 129 
#define  jbvString 128 
 int /*<<< orphan*/ * newSV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newSVnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numeric_out ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pnstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SV  *
JsonbValue_to_SV(JsonbValue *jbv)
{
	dTHX;

	switch (jbv->type)
	{
		case jbvBinary:
			return Jsonb_to_SV(jbv->val.binary.data);

		case jbvNumeric:
			{
				char	   *str = DatumGetCString(DirectFunctionCall1(numeric_out,
																	  NumericGetDatum(jbv->val.numeric)));
				SV		   *result = newSVnv(SvNV(cstr2sv(str)));

				pfree(str);
				return result;
			}

		case jbvString:
			{
				char	   *str = pnstrdup(jbv->val.string.val,
										   jbv->val.string.len);
				SV		   *result = cstr2sv(str);

				pfree(str);
				return result;
			}

		case jbvBool:
			return newSVnv(SvNV(jbv->val.boolean ? &PL_sv_yes : &PL_sv_no));

		case jbvNull:
			return newSV(0);

		default:
			elog(ERROR, "unexpected jsonb value type: %d", jbv->type);
			return NULL;
	}
}