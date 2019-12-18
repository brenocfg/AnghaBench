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
typedef  int /*<<< orphan*/  tsearch_readline_state ;
struct TYPE_7__ {int len; TYPE_1__* syn; int /*<<< orphan*/  matchsynonyms; scalar_t__ matchorig; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Syn ;
typedef  TYPE_2__ DictSyn ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  compare_syn ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* find_word (char*,char**) ; 
 char* get_tsearch_config_filename (char const*,char*) ; 
 char* lowerstr (char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pnstrdup (char*,int) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (TYPE_1__*,int) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
read_dictionary(DictSyn *d, const char *filename)
{
	char	   *real_filename = get_tsearch_config_filename(filename, "rules");
	tsearch_readline_state trst;
	char	   *line;
	int			cur = 0;

	if (!tsearch_readline_begin(&trst, real_filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open synonym file \"%s\": %m",
						real_filename)));

	while ((line = tsearch_readline(&trst)) != NULL)
	{
		char	   *value;
		char	   *key;
		char	   *pos;
		char	   *end;

		if (*line == '\0')
			continue;

		value = lowerstr(line);
		pfree(line);

		pos = value;
		while ((key = find_word(pos, &end)) != NULL)
		{
			/* Enlarge syn structure if full */
			if (cur == d->len)
			{
				d->len = (d->len > 0) ? 2 * d->len : 16;
				if (d->syn)
					d->syn = (Syn *) repalloc(d->syn, sizeof(Syn) * d->len);
				else
					d->syn = (Syn *) palloc(sizeof(Syn) * d->len);
			}

			/* Save first word only if we will match it */
			if (pos != value || d->matchorig)
			{
				d->syn[cur].key = pnstrdup(key, end - key);
				d->syn[cur].value = pstrdup(value);

				cur++;
			}

			pos = end;

			/* Don't bother scanning synonyms if we will not match them */
			if (!d->matchsynonyms)
				break;
		}

		pfree(value);
	}

	tsearch_readline_end(&trst);

	d->len = cur;
	if (cur > 1)
		qsort(d->syn, d->len, sizeof(Syn), compare_syn);

	pfree(real_filename);
}