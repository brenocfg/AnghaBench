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
struct TYPE_3__ {char* name; char* ident; } ;
typedef  TYPE_1__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int pg_mbcliplen (char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
MemoryContextStatsPrint(MemoryContext context, void *passthru,
						const char *stats_string)
{
	int			level = *(int *) passthru;
	const char *name = context->name;
	const char *ident = context->ident;
	int			i;

	/*
	 * It seems preferable to label dynahash contexts with just the hash table
	 * name.  Those are already unique enough, so the "dynahash" part isn't
	 * very helpful, and this way is more consistent with pre-v11 practice.
	 */
	if (ident && strcmp(name, "dynahash") == 0)
	{
		name = ident;
		ident = NULL;
	}

	for (i = 0; i < level; i++)
		fprintf(stderr, "  ");
	fprintf(stderr, "%s: %s", name, stats_string);
	if (ident)
	{
		/*
		 * Some contexts may have very long identifiers (e.g., SQL queries).
		 * Arbitrarily truncate at 100 bytes, but be careful not to break
		 * multibyte characters.  Also, replace ASCII control characters, such
		 * as newlines, with spaces.
		 */
		int			idlen = strlen(ident);
		bool		truncated = false;

		if (idlen > 100)
		{
			idlen = pg_mbcliplen(ident, idlen, 100);
			truncated = true;
		}
		fprintf(stderr, ": ");
		while (idlen-- > 0)
		{
			unsigned char c = *ident++;

			if (c < ' ')
				c = ' ';
			fputc(c, stderr);
		}
		if (truncated)
			fprintf(stderr, "...");
	}
	fputc('\n', stderr);
}