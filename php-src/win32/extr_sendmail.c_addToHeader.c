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
 char* erealloc (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int addToHeader(char **header_buffer, const char *specifier, char *string)
{
	*header_buffer = erealloc(*header_buffer, strlen(*header_buffer) + strlen(specifier) + strlen(string) + 1);
	sprintf(*header_buffer + strlen(*header_buffer), specifier, string);
	return 1;
}