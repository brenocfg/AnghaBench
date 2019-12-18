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
struct TYPE_3__ {scalar_t__ token; } ;
typedef  TYPE_1__ datetkn ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 scalar_t__ TOKMAXLEN ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,scalar_t__,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static bool
CheckDateTokenTable(const char *tablename, const datetkn *base, int nel)
{
	bool		ok = true;
	int			i;

	for (i = 0; i < nel; i++)
	{
		/* check for token strings that don't fit */
		if (strlen(base[i].token) > TOKMAXLEN)
		{
			/* %.*s is safe since all our tokens are ASCII */
			elog(LOG, "token too long in %s table: \"%.*s\"",
				 tablename,
				 TOKMAXLEN + 1, base[i].token);
			ok = false;
			break;				/* don't risk applying strcmp */
		}
		/* check for out of order */
		if (i > 0 &&
			strcmp(base[i - 1].token, base[i].token) >= 0)
		{
			elog(LOG, "ordering error in %s table: \"%s\" >= \"%s\"",
				 tablename,
				 base[i - 1].token,
				 base[i].token);
			ok = false;
		}
	}
	return ok;
}