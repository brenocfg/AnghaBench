#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsearch_readline_state ;
struct TYPE_3__ {int len; char** stop; } ;
typedef  TYPE_1__ StopList ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_tsearch_config_filename (char const*,char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 int /*<<< orphan*/  pg_qsort_strcmp ; 
 int /*<<< orphan*/  qsort (char**,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (void*,int) ; 
 int /*<<< orphan*/  t_isspace (char*) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

void
readstoplist(const char *fname, StopList *s, char *(*wordop) (const char *))
{
	char	  **stop = NULL;

	s->len = 0;
	if (fname && *fname)
	{
		char	   *filename = get_tsearch_config_filename(fname, "stop");
		tsearch_readline_state trst;
		char	   *line;
		int			reallen = 0;

		if (!tsearch_readline_begin(&trst, filename))
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("could not open stop-word file \"%s\": %m",
							filename)));

		while ((line = tsearch_readline(&trst)) != NULL)
		{
			char	   *pbuf = line;

			/* Trim trailing space */
			while (*pbuf && !t_isspace(pbuf))
				pbuf += pg_mblen(pbuf);
			*pbuf = '\0';

			/* Skip empty lines */
			if (*line == '\0')
			{
				pfree(line);
				continue;
			}

			if (s->len >= reallen)
			{
				if (reallen == 0)
				{
					reallen = 64;
					stop = (char **) palloc(sizeof(char *) * reallen);
				}
				else
				{
					reallen *= 2;
					stop = (char **) repalloc((void *) stop,
											  sizeof(char *) * reallen);
				}
			}

			if (wordop)
			{
				stop[s->len] = wordop(line);
				if (stop[s->len] != line)
					pfree(line);
			}
			else
				stop[s->len] = line;

			(s->len)++;
		}

		tsearch_readline_end(&trst);
		pfree(filename);
	}

	s->stop = stop;

	/* Sort to allow binary searching */
	if (s->stop && s->len > 0)
		qsort(s->stop, s->len, sizeof(char *), pg_qsort_strcmp);
}