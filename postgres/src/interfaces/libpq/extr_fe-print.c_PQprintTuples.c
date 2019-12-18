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
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/  const*,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libpq_gettext (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
PQprintTuples(const PGresult *res,
			  FILE *fout,		/* output stream */
			  int PrintAttNames,	/* print attribute names or not */
			  int TerseOutput,	/* delimiter bars or not? */
			  int colWidth		/* width of column, if 0, use variable width */
)
{
	int			nFields;
	int			nTups;
	int			i,
				j;
	char		formatString[80];
	char	   *tborder = NULL;

	nFields = PQnfields(res);
	nTups = PQntuples(res);

	if (colWidth > 0)
		sprintf(formatString, "%%s %%-%ds", colWidth);
	else
		sprintf(formatString, "%%s %%s");

	if (nFields > 0)
	{							/* only print rows with at least 1 field.  */

		if (!TerseOutput)
		{
			int			width;

			width = nFields * 14;
			tborder = (char *) malloc(width + 1);
			if (!tborder)
			{
				fprintf(stderr, libpq_gettext("out of memory\n"));
				abort();
			}
			for (i = 0; i < width; i++)
				tborder[i] = '-';
			tborder[width] = '\0';
			fprintf(fout, "%s\n", tborder);
		}

		for (i = 0; i < nFields; i++)
		{
			if (PrintAttNames)
			{
				fprintf(fout, formatString,
						TerseOutput ? "" : "|",
						PQfname(res, i));
			}
		}

		if (PrintAttNames)
		{
			if (TerseOutput)
				fprintf(fout, "\n");
			else
				fprintf(fout, "|\n%s\n", tborder);
		}

		for (i = 0; i < nTups; i++)
		{
			for (j = 0; j < nFields; j++)
			{
				const char *pval = PQgetvalue(res, i, j);

				fprintf(fout, formatString,
						TerseOutput ? "" : "|",
						pval ? pval : "");
			}
			if (TerseOutput)
				fprintf(fout, "\n");
			else
				fprintf(fout, "|\n%s\n", tborder);
		}
	}

	if (tborder)
		free(tborder);
}