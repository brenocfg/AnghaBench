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
typedef  char WCHAR ;
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  strncmpiW (char*,char const*,int) ; 

__attribute__((used)) static LPCWSTR COMM_ParseStart(LPCWSTR ptr)
{
	static const WCHAR comW[] = {'C','O','M',0};

	/* The device control string may optionally start with "COMx" followed
	   by an optional ':' and spaces. */
	if(!strncmpiW(ptr, comW, 3))
	{
		ptr += 3;

		/* Allow any com port above 0 as Win 9x does (NT only allows
		   values for com ports which are actually present) */
		if(*ptr < '1' || *ptr > '9')
			return NULL;
		
		/* Advance pointer past port number */
		while(*ptr >= '0' && *ptr <= '9') ptr++;
		
		/* The com port number must be followed by a ':' or ' ' */
		if(*ptr != ':' && *ptr != ' ')
			return NULL;

		/* Advance pointer to beginning of next parameter */
		while(*ptr == ' ') ptr++;
		if(*ptr == ':')
		{
			ptr++;
			while(*ptr == ' ') ptr++;
		}
	}
	/* The device control string must not start with a space. */
	else if(*ptr == ' ')
		return NULL;
	
	return ptr;
}