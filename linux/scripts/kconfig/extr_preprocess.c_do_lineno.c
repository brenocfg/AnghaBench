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
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* xstrdup (char*) ; 
 int yylineno ; 

__attribute__((used)) static char *do_lineno(int argc, char *argv[])
{
	char buf[16];

	sprintf(buf, "%d", yylineno);

	return xstrdup(buf);
}