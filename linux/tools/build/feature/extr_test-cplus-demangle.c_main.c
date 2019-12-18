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
 char* cplus_demangle (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int main(void)
{
	char symbol[4096] = "FieldName__9ClassNameFd";
	char *tmp;

	tmp = cplus_demangle(symbol, 0);

	printf("demangled symbol: {%s}\n", tmp);

	return 0;
}