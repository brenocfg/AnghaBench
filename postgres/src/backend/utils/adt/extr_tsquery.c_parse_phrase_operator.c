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
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_3__ {char* buf; } ;
typedef  TYPE_1__* TSQueryParserState ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 long MAXENTRYPOS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,long) ; 
 int /*<<< orphan*/  errno ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  t_isdigit (char*) ; 
 int /*<<< orphan*/  t_iseq (char*,char) ; 

__attribute__((used)) static bool
parse_phrase_operator(TSQueryParserState pstate, int16 *distance)
{
	enum
	{
		PHRASE_OPEN = 0,
		PHRASE_DIST,
		PHRASE_CLOSE,
		PHRASE_FINISH
	}			state = PHRASE_OPEN;
	char	   *ptr = pstate->buf;
	char	   *endptr;
	long		l = 1;			/* default distance */

	while (*ptr)
	{
		switch (state)
		{
			case PHRASE_OPEN:
				if (t_iseq(ptr, '<'))
				{
					state = PHRASE_DIST;
					ptr++;
				}
				else
					return false;
				break;

			case PHRASE_DIST:
				if (t_iseq(ptr, '-'))
				{
					state = PHRASE_CLOSE;
					ptr++;
					continue;
				}

				if (!t_isdigit(ptr))
					return false;

				errno = 0;
				l = strtol(ptr, &endptr, 10);
				if (ptr == endptr)
					return false;
				else if (errno == ERANGE || l < 0 || l > MAXENTRYPOS)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("distance in phrase operator should not be greater than %d",
									MAXENTRYPOS)));
				else
				{
					state = PHRASE_CLOSE;
					ptr = endptr;
				}
				break;

			case PHRASE_CLOSE:
				if (t_iseq(ptr, '>'))
				{
					state = PHRASE_FINISH;
					ptr++;
				}
				else
					return false;
				break;

			case PHRASE_FINISH:
				*distance = (int16) l;
				pstate->buf = ptr;
				return true;
		}
	}

	return false;
}