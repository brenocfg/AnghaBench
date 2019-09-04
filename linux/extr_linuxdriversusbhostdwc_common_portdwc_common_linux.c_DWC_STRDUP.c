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
 char* DWC_ALLOC_ATOMIC (int) ; 
 int /*<<< orphan*/  DWC_MEMCPY (char*,char const*,int) ; 
 int DWC_STRLEN (char const*) ; 

char *DWC_STRDUP(char const *str)
{
	int len = DWC_STRLEN(str) + 1;
	char *new = DWC_ALLOC_ATOMIC(len);

	if (!new) {
		return NULL;
	}

	DWC_MEMCPY(new, str, len);
	return new;
}