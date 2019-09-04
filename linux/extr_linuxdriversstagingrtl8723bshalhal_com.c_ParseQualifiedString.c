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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

bool ParseQualifiedString(
	char *In, u32 *Start, char *Out, char LeftQualifier, char RightQualifier
)
{
	u32 i = 0, j = 0;
	char c = In[(*Start)++];

	if (c != LeftQualifier)
		return false;

	i = (*Start);
	while ((c = In[(*Start)++]) != RightQualifier)
		; /*  find ']' */
	j = (*Start) - 2;
	strncpy((char *)Out, (const char *)(In+i), j-i+1);

	return true;
}