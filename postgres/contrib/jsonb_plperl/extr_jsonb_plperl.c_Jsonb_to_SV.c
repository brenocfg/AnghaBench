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
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int /*<<< orphan*/  rawScalar; } ;
struct TYPE_9__ {TYPE_2__ string; TYPE_1__ array; } ;
struct TYPE_10__ {TYPE_3__ val; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_4__ JsonbValue ;
typedef  int JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  JsonbContainer ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 int JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * JsonbValue_to_SV (TYPE_4__*) ; 
#define  WJB_BEGIN_ARRAY 129 
#define  WJB_BEGIN_OBJECT 128 
 int WJB_DONE ; 
 int WJB_ELEM ; 
 int WJB_END_ARRAY ; 
 int WJB_KEY ; 
 int WJB_VALUE ; 
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hv_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SV  *
Jsonb_to_SV(JsonbContainer *jsonb)
{
	dTHX;
	JsonbValue	v;
	JsonbIterator *it;
	JsonbIteratorToken r;

	it = JsonbIteratorInit(jsonb);
	r = JsonbIteratorNext(&it, &v, true);

	switch (r)
	{
		case WJB_BEGIN_ARRAY:
			if (v.val.array.rawScalar)
			{
				JsonbValue	tmp;

				if ((r = JsonbIteratorNext(&it, &v, true)) != WJB_ELEM ||
					(r = JsonbIteratorNext(&it, &tmp, true)) != WJB_END_ARRAY ||
					(r = JsonbIteratorNext(&it, &tmp, true)) != WJB_DONE)
					elog(ERROR, "unexpected jsonb token: %d", r);

				return JsonbValue_to_SV(&v);
			}
			else
			{
				AV		   *av = newAV();

				while ((r = JsonbIteratorNext(&it, &v, true)) != WJB_DONE)
				{
					if (r == WJB_ELEM)
						av_push(av, JsonbValue_to_SV(&v));
				}

				return newRV((SV *) av);
			}

		case WJB_BEGIN_OBJECT:
			{
				HV		   *hv = newHV();

				while ((r = JsonbIteratorNext(&it, &v, true)) != WJB_DONE)
				{
					if (r == WJB_KEY)
					{
						/* json key in v, json value in val */
						JsonbValue	val;

						if (JsonbIteratorNext(&it, &val, true) == WJB_VALUE)
						{
							SV		   *value = JsonbValue_to_SV(&val);

							(void) hv_store(hv,
											v.val.string.val, v.val.string.len,
											value, 0);
						}
					}
				}

				return newRV((SV *) hv);
			}

		default:
			elog(ERROR, "unexpected jsonb token: %d", r);
			return NULL;
	}
}