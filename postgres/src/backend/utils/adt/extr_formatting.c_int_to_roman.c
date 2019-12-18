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
typedef  int /*<<< orphan*/  numstr ;

/* Variables and functions */
 int /*<<< orphan*/  fill_str (char*,char,int) ; 
 scalar_t__ palloc (int) ; 
 char** rm1 ; 
 char** rm10 ; 
 char** rm100 ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static char *
int_to_roman(int number)
{
	int			len = 0,
				num = 0;
	char	   *p = NULL,
			   *result,
				numstr[12];

	result = (char *) palloc(16);
	*result = '\0';

	if (number > 3999 || number < 1)
	{
		fill_str(result, '#', 15);
		return result;
	}
	len = snprintf(numstr, sizeof(numstr), "%d", number);

	for (p = numstr; *p != '\0'; p++, --len)
	{
		num = *p - 49;			/* 48 ascii + 1 */
		if (num < 0)
			continue;

		if (len > 3)
		{
			while (num-- != -1)
				strcat(result, "M");
		}
		else
		{
			if (len == 3)
				strcat(result, rm100[num]);
			else if (len == 2)
				strcat(result, rm10[num]);
			else if (len == 1)
				strcat(result, rm1[num]);
		}
	}
	return result;
}