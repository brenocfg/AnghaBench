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

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  PAE_WAIT_FIND 132 
#define  PAE_WAIT_FLAG 131 
#define  PAE_WAIT_MASK 130 
#define  PAE_WAIT_REPL 129 
#define  PAE_WAIT_TYPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int get_nextfield (char**,char*) ; 

__attribute__((used)) static int
parse_ooaffentry(char *str, char *type, char *flag, char *find,
				 char *repl, char *mask)
{
	int			state = PAE_WAIT_TYPE;
	int			fields_read = 0;
	bool		valid = false;

	*type = *flag = *find = *repl = *mask = '\0';

	while (*str)
	{
		switch (state)
		{
			case PAE_WAIT_TYPE:
				valid = get_nextfield(&str, type);
				state = PAE_WAIT_FLAG;
				break;
			case PAE_WAIT_FLAG:
				valid = get_nextfield(&str, flag);
				state = PAE_WAIT_FIND;
				break;
			case PAE_WAIT_FIND:
				valid = get_nextfield(&str, find);
				state = PAE_WAIT_REPL;
				break;
			case PAE_WAIT_REPL:
				valid = get_nextfield(&str, repl);
				state = PAE_WAIT_MASK;
				break;
			case PAE_WAIT_MASK:
				valid = get_nextfield(&str, mask);
				state = -1;		/* force loop exit */
				break;
			default:
				elog(ERROR, "unrecognized state in parse_ooaffentry: %d",
					 state);
				break;
		}
		if (valid)
			fields_read++;
		else
			break;				/* early EOL */
		if (state < 0)
			break;				/* got all fields */
	}

	return fields_read;
}