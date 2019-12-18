#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DEFAULT_FIELD_SEP ; 
 char* PQfname (int /*<<< orphan*/  const*,int) ; 
 int PQgetlength (int /*<<< orphan*/  const*,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill (int,int,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 char* libpq_gettext (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int strlen (char*) ; 

void
PQdisplayTuples(const PGresult *res,
				FILE *fp,		/* where to send the output */
				int fillAlign,	/* pad the fields with spaces */
				const char *fieldSep,	/* field separator */
				int printHeader,	/* display headers? */
				int quiet
)
{
#define DEFAULT_FIELD_SEP " "

	int			i,
				j;
	int			nFields;
	int			nTuples;
	int		   *fLength = NULL;

	if (fieldSep == NULL)
		fieldSep = DEFAULT_FIELD_SEP;

	/* Get some useful info about the results */
	nFields = PQnfields(res);
	nTuples = PQntuples(res);

	if (fp == NULL)
		fp = stdout;

	/* Figure the field lengths to align to */
	/* will be somewhat time consuming for very large results */
	if (fillAlign)
	{
		fLength = (int *) malloc(nFields * sizeof(int));
		if (!fLength)
		{
			fprintf(stderr, libpq_gettext("out of memory\n"));
			abort();
		}

		for (j = 0; j < nFields; j++)
		{
			fLength[j] = strlen(PQfname(res, j));
			for (i = 0; i < nTuples; i++)
			{
				int			flen = PQgetlength(res, i, j);

				if (flen > fLength[j])
					fLength[j] = flen;
			}
		}
	}

	if (printHeader)
	{
		/* first, print out the attribute names */
		for (i = 0; i < nFields; i++)
		{
			fputs(PQfname(res, i), fp);
			if (fillAlign)
				fill(strlen(PQfname(res, i)), fLength[i], ' ', fp);
			fputs(fieldSep, fp);
		}
		fprintf(fp, "\n");

		/* Underline the attribute names */
		for (i = 0; i < nFields; i++)
		{
			if (fillAlign)
				fill(0, fLength[i], '-', fp);
			fputs(fieldSep, fp);
		}
		fprintf(fp, "\n");
	}

	/* next, print out the instances */
	for (i = 0; i < nTuples; i++)
	{
		for (j = 0; j < nFields; j++)
		{
			fprintf(fp, "%s", PQgetvalue(res, i, j));
			if (fillAlign)
				fill(strlen(PQgetvalue(res, i, j)), fLength[j], ' ', fp);
			fputs(fieldSep, fp);
		}
		fprintf(fp, "\n");
	}

	if (!quiet)
		fprintf(fp, "\nQuery returned %d row%s.\n", PQntuples(res),
				(PQntuples(res) == 1) ? "" : "s");

	fflush(fp);

	if (fLength)
		free(fLength);
}