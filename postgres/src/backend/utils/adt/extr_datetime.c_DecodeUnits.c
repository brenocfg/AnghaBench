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
struct TYPE_4__ {int type; int value; int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ datetkn ;

/* Variables and functions */
 int /*<<< orphan*/  TOKMAXLEN ; 
 int UNKNOWN_FIELD ; 
 TYPE_1__* datebsearch (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ const** deltacache ; 
 int /*<<< orphan*/  deltatktbl ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szdeltatktbl ; 

int
DecodeUnits(int field, char *lowtoken, int *val)
{
	int			type;
	const datetkn *tp;

	tp = deltacache[field];
	/* use strncmp so that we match truncated tokens */
	if (tp == NULL || strncmp(lowtoken, tp->token, TOKMAXLEN) != 0)
	{
		tp = datebsearch(lowtoken, deltatktbl, szdeltatktbl);
	}
	if (tp == NULL)
	{
		type = UNKNOWN_FIELD;
		*val = 0;
	}
	else
	{
		deltacache[field] = tp;
		type = tp->type;
		*val = tp->value;
	}

	return type;
}