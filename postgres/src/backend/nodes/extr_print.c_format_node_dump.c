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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int LINELEN ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

char *
format_node_dump(const char *dump)
{
#define LINELEN		78
	char		line[LINELEN + 1];
	StringInfoData str;
	int			i;
	int			j;
	int			k;

	initStringInfo(&str);
	i = 0;
	for (;;)
	{
		for (j = 0; j < LINELEN && dump[i] != '\0'; i++, j++)
			line[j] = dump[i];
		if (dump[i] == '\0')
			break;
		if (dump[i] == ' ')
		{
			/* ok to break at adjacent space */
			i++;
		}
		else
		{
			for (k = j - 1; k > 0; k--)
				if (line[k] == ' ')
					break;
			if (k > 0)
			{
				/* back up; will reprint all after space */
				i -= (j - k - 1);
				j = k;
			}
		}
		line[j] = '\0';
		appendStringInfo(&str, "%s\n", line);
	}
	if (j > 0)
	{
		line[j] = '\0';
		appendStringInfo(&str, "%s\n", line);
	}
	return str.data;
#undef LINELEN
}