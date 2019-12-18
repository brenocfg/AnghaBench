#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  long uint32 ;
struct TYPE_26__ {int /*<<< orphan*/  root; } ;
struct TYPE_23__ {int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {TYPE_1__ binary; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbContainer ;
typedef  TYPE_4__ Jsonb ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_4__* Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 long INT_MAX ; 
 long INT_MIN ; 
 int IsAJsonbScalar (TYPE_3__*) ; 
 scalar_t__ JB_ROOT_IS_ARRAY (TYPE_4__*) ; 
 scalar_t__ JB_ROOT_IS_OBJECT (TYPE_4__*) ; 
 scalar_t__ JB_ROOT_IS_SCALAR (TYPE_4__*) ; 
 int JsonContainerIsArray (int /*<<< orphan*/ *) ; 
 int JsonContainerIsObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonContainerIsScalar (int /*<<< orphan*/ *) ; 
 long JsonContainerSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonbToCString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  JsonbValueAsText (TYPE_3__*) ; 
 TYPE_4__* JsonbValueToJsonb (TYPE_3__*) ; 
 int /*<<< orphan*/ * PG_GETARG_ARRAYTYPE_P (int) ; 
 TYPE_4__* PG_GETARG_JSONB_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_JSONB_P (TYPE_4__*) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 int /*<<< orphan*/  PG_RETURN_TEXT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (TYPE_4__*) ; 
 int /*<<< orphan*/  VARDATA (TYPE_4__*) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (TYPE_4__*) ; 
 scalar_t__ array_contains_nulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,TYPE_4__***,int**,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 TYPE_3__* getIthJsonbValueFromContainer (int /*<<< orphan*/ *,long) ; 
 TYPE_3__* getKeyJsonValueFromContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 scalar_t__ jbvBinary ; 
 scalar_t__ jbvNull ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static Datum
get_jsonb_path_all(FunctionCallInfo fcinfo, bool as_text)
{
	Jsonb	   *jb = PG_GETARG_JSONB_P(0);
	ArrayType  *path = PG_GETARG_ARRAYTYPE_P(1);
	Datum	   *pathtext;
	bool	   *pathnulls;
	int			npath;
	int			i;
	bool		have_object = false,
				have_array = false;
	JsonbValue *jbvp = NULL;
	JsonbValue	jbvbuf;
	JsonbContainer *container;

	/*
	 * If the array contains any null elements, return NULL, on the grounds
	 * that you'd have gotten NULL if any RHS value were NULL in a nested
	 * series of applications of the -> operator.  (Note: because we also
	 * return NULL for error cases such as no-such-field, this is true
	 * regardless of the contents of the rest of the array.)
	 */
	if (array_contains_nulls(path))
		PG_RETURN_NULL();

	deconstruct_array(path, TEXTOID, -1, false, 'i',
					  &pathtext, &pathnulls, &npath);

	/* Identify whether we have object, array, or scalar at top-level */
	container = &jb->root;

	if (JB_ROOT_IS_OBJECT(jb))
		have_object = true;
	else if (JB_ROOT_IS_ARRAY(jb) && !JB_ROOT_IS_SCALAR(jb))
		have_array = true;
	else
	{
		Assert(JB_ROOT_IS_ARRAY(jb) && JB_ROOT_IS_SCALAR(jb));
		/* Extract the scalar value, if it is what we'll return */
		if (npath <= 0)
			jbvp = getIthJsonbValueFromContainer(container, 0);
	}

	/*
	 * If the array is empty, return the entire LHS object, on the grounds
	 * that we should do zero field or element extractions.  For the
	 * non-scalar case we can just hand back the object without much work. For
	 * the scalar case, fall through and deal with the value below the loop.
	 * (This inconsistency arises because there's no easy way to generate a
	 * JsonbValue directly for root-level containers.)
	 */
	if (npath <= 0 && jbvp == NULL)
	{
		if (as_text)
		{
			PG_RETURN_TEXT_P(cstring_to_text(JsonbToCString(NULL,
															container,
															VARSIZE(jb))));
		}
		else
		{
			/* not text mode - just hand back the jsonb */
			PG_RETURN_JSONB_P(jb);
		}
	}

	for (i = 0; i < npath; i++)
	{
		if (have_object)
		{
			jbvp = getKeyJsonValueFromContainer(container,
												VARDATA(pathtext[i]),
												VARSIZE(pathtext[i]) - VARHDRSZ,
												&jbvbuf);
		}
		else if (have_array)
		{
			long		lindex;
			uint32		index;
			char	   *indextext = TextDatumGetCString(pathtext[i]);
			char	   *endptr;

			errno = 0;
			lindex = strtol(indextext, &endptr, 10);
			if (endptr == indextext || *endptr != '\0' || errno != 0 ||
				lindex > INT_MAX || lindex < INT_MIN)
				PG_RETURN_NULL();

			if (lindex >= 0)
			{
				index = (uint32) lindex;
			}
			else
			{
				/* Handle negative subscript */
				uint32		nelements;

				/* Container must be array, but make sure */
				if (!JsonContainerIsArray(container))
					elog(ERROR, "not a jsonb array");

				nelements = JsonContainerSize(container);

				if (-lindex > nelements)
					PG_RETURN_NULL();
				else
					index = nelements + lindex;
			}

			jbvp = getIthJsonbValueFromContainer(container, index);
		}
		else
		{
			/* scalar, extraction yields a null */
			PG_RETURN_NULL();
		}

		if (jbvp == NULL)
			PG_RETURN_NULL();
		else if (i == npath - 1)
			break;

		if (jbvp->type == jbvBinary)
		{
			container = jbvp->val.binary.data;
			have_object = JsonContainerIsObject(container);
			have_array = JsonContainerIsArray(container);
			Assert(!JsonContainerIsScalar(container));
		}
		else
		{
			Assert(IsAJsonbScalar(jbvp));
			have_object = false;
			have_array = false;
		}
	}

	if (as_text)
	{
		if (jbvp->type == jbvNull)
			PG_RETURN_NULL();

		PG_RETURN_TEXT_P(JsonbValueAsText(jbvp));
	}
	else
	{
		Jsonb	   *res = JsonbValueToJsonb(jbvp);

		/* not text mode - just hand back the jsonb */
		PG_RETURN_JSONB_P(res);
	}
}