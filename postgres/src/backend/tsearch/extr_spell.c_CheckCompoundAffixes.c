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
struct TYPE_3__ {int len; int issuffix; scalar_t__ affix; } ;
typedef  TYPE_1__ CMPDAffix ;

/* Variables and functions */
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 char* strstr (char*,scalar_t__) ; 

__attribute__((used)) static int
CheckCompoundAffixes(CMPDAffix **ptr, char *word, int len, bool CheckInPlace)
{
	bool		issuffix;

	/* in case CompoundAffix is null: */
	if (*ptr == NULL)
		return -1;

	if (CheckInPlace)
	{
		while ((*ptr)->affix)
		{
			if (len > (*ptr)->len && strncmp((*ptr)->affix, word, (*ptr)->len) == 0)
			{
				len = (*ptr)->len;
				issuffix = (*ptr)->issuffix;
				(*ptr)++;
				return (issuffix) ? len : 0;
			}
			(*ptr)++;
		}
	}
	else
	{
		char	   *affbegin;

		while ((*ptr)->affix)
		{
			if (len > (*ptr)->len && (affbegin = strstr(word, (*ptr)->affix)) != NULL)
			{
				len = (*ptr)->len + (affbegin - word);
				issuffix = (*ptr)->issuffix;
				(*ptr)++;
				return (issuffix) ? len : 0;
			}
			(*ptr)++;
		}
	}
	return -1;
}