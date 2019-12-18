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
struct TYPE_6__ {int isset; TYPE_2__* gen; } ;
typedef  TYPE_1__ relopt_value ;
typedef  int relopt_kind ;
struct TYPE_7__ {int kinds; int namelen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 void* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PointerIsValid (void*) ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 char* VARDATA (int /*<<< orphan*/ ) ; 
 int VARHDRSZ ; 
 int VARSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  initialize_reloptions () ; 
 scalar_t__ need_initialization ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  parse_one_reloption (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 TYPE_2__** relOpts ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static relopt_value *
parseRelOptions(Datum options, bool validate, relopt_kind kind,
				int *numrelopts)
{
	relopt_value *reloptions = NULL;
	int			numoptions = 0;
	int			i;
	int			j;

	if (need_initialization)
		initialize_reloptions();

	/* Build a list of expected options, based on kind */

	for (i = 0; relOpts[i]; i++)
		if (relOpts[i]->kinds & kind)
			numoptions++;

	if (numoptions > 0)
	{
		reloptions = palloc(numoptions * sizeof(relopt_value));

		for (i = 0, j = 0; relOpts[i]; i++)
		{
			if (relOpts[i]->kinds & kind)
			{
				reloptions[j].gen = relOpts[i];
				reloptions[j].isset = false;
				j++;
			}
		}
	}

	/* Done if no options */
	if (PointerIsValid(DatumGetPointer(options)))
	{
		ArrayType  *array = DatumGetArrayTypeP(options);
		Datum	   *optiondatums;
		int			noptions;

		deconstruct_array(array, TEXTOID, -1, false, 'i',
						  &optiondatums, NULL, &noptions);

		for (i = 0; i < noptions; i++)
		{
			char	   *text_str = VARDATA(optiondatums[i]);
			int			text_len = VARSIZE(optiondatums[i]) - VARHDRSZ;
			int			j;

			/* Search for a match in reloptions */
			for (j = 0; j < numoptions; j++)
			{
				int			kw_len = reloptions[j].gen->namelen;

				if (text_len > kw_len && text_str[kw_len] == '=' &&
					strncmp(text_str, reloptions[j].gen->name, kw_len) == 0)
				{
					parse_one_reloption(&reloptions[j], text_str, text_len,
										validate);
					break;
				}
			}

			if (j >= numoptions && validate)
			{
				char	   *s;
				char	   *p;

				s = TextDatumGetCString(optiondatums[i]);
				p = strchr(s, '=');
				if (p)
					*p = '\0';
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("unrecognized parameter \"%s\"", s)));
			}
		}

		/* It's worth avoiding memory leaks in this function */
		pfree(optiondatums);
		if (((void *) array) != DatumGetPointer(options))
			pfree(array);
	}

	*numrelopts = numoptions;
	return reloptions;
}