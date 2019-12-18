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
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 char DELIM ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 char LDELIM ; 
 char LDELIM_EP ; 
 char RDELIM ; 
 char RDELIM_EP ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pair_decode (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,char const*,char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
path_decode(char *str, bool opentype, int npts, Point *p,
			bool *isopen, char **endptr_p,
			const char *type_name, const char *orig_string)
{
	int			depth = 0;
	char	   *cp;
	int			i;

	while (isspace((unsigned char) *str))
		str++;
	if ((*isopen = (*str == LDELIM_EP)))
	{
		/* no open delimiter allowed? */
		if (!opentype)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("invalid input syntax for type %s: \"%s\"",
							type_name, orig_string)));
		depth++;
		str++;
	}
	else if (*str == LDELIM)
	{
		cp = (str + 1);
		while (isspace((unsigned char) *cp))
			cp++;
		if (*cp == LDELIM)
		{
			depth++;
			str = cp;
		}
		else if (strrchr(str, LDELIM) == str)
		{
			depth++;
			str = cp;
		}
	}

	for (i = 0; i < npts; i++)
	{
		pair_decode(str, &(p->x), &(p->y), &str, type_name, orig_string);
		if (*str == DELIM)
			str++;
		p++;
	}

	while (depth > 0)
	{
		if (*str == RDELIM || (*str == RDELIM_EP && *isopen && depth == 1))
		{
			depth--;
			str++;
			while (isspace((unsigned char) *str))
				str++;
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("invalid input syntax for type %s: \"%s\"",
							type_name, orig_string)));
	}

	/* report stopping point if wanted, else complain if not end of string */
	if (endptr_p)
		*endptr_p = str;
	else if (*str != '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						type_name, orig_string)));
}