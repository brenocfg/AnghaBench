#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pg_tz ;
struct TYPE_7__ {int type; int value; int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ datetkn ;
struct TYPE_8__ {int /*<<< orphan*/  numabbrevs; int /*<<< orphan*/  abbrevs; } ;

/* Variables and functions */
 int DYNTZ ; 
 int /*<<< orphan*/ * FetchDynamicTimeZone (TYPE_2__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TOKMAXLEN ; 
 int UNKNOWN_FIELD ; 
 TYPE_1__ const** abbrevcache ; 
 TYPE_1__* datebsearch (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zoneabbrevtbl ; 

int
DecodeTimezoneAbbrev(int field, char *lowtoken,
					 int *offset, pg_tz **tz)
{
	int			type;
	const datetkn *tp;

	tp = abbrevcache[field];
	/* use strncmp so that we match truncated tokens */
	if (tp == NULL || strncmp(lowtoken, tp->token, TOKMAXLEN) != 0)
	{
		if (zoneabbrevtbl)
			tp = datebsearch(lowtoken, zoneabbrevtbl->abbrevs,
							 zoneabbrevtbl->numabbrevs);
		else
			tp = NULL;
	}
	if (tp == NULL)
	{
		type = UNKNOWN_FIELD;
		*offset = 0;
		*tz = NULL;
	}
	else
	{
		abbrevcache[field] = tp;
		type = tp->type;
		if (type == DYNTZ)
		{
			*offset = 0;
			*tz = FetchDynamicTimeZone(zoneabbrevtbl, tp);
		}
		else
		{
			*offset = tp->value;
			*tz = NULL;
		}
	}

	return type;
}