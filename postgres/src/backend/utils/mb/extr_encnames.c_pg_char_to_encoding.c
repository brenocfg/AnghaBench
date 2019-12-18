#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int encoding; } ;
typedef  TYPE_1__ pg_encname ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NAME_TOO_LONG ; 
 int /*<<< orphan*/  ERROR ; 
 int NAMEDATALEN ; 
 char* clean_encoding_name (char const*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 unsigned int lengthof (TYPE_1__*) ; 
 TYPE_1__* pg_encname_tbl ; 
 int /*<<< orphan*/  stderr ; 
 int strcmp (char*,char*) ; 
 int strlen (char const*) ; 

int
pg_char_to_encoding(const char *name)
{
	unsigned int nel = lengthof(pg_encname_tbl);
	const pg_encname *base = pg_encname_tbl,
			   *last = base + nel - 1,
			   *position;
	int			result;
	char		buff[NAMEDATALEN],
			   *key;

	if (name == NULL || *name == '\0')
		return -1;

	if (strlen(name) >= NAMEDATALEN)
	{
#ifdef FRONTEND
		fprintf(stderr, "encoding name too long\n");
		return -1;
#else
		ereport(ERROR,
				(errcode(ERRCODE_NAME_TOO_LONG),
				 errmsg("encoding name too long")));
#endif
	}
	key = clean_encoding_name(name, buff);

	while (last >= base)
	{
		position = base + ((last - base) >> 1);
		result = key[0] - position->name[0];

		if (result == 0)
		{
			result = strcmp(key, position->name);
			if (result == 0)
				return position->encoding;
		}
		if (result < 0)
			last = position - 1;
		else
			base = position + 1;
	}
	return -1;
}