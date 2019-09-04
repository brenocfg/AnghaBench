#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* current_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* xstrdup (char*) ; 
 int yylineno ; 

__attribute__((used)) static char *do_warning_if(int argc, char *argv[])
{
	if (!strcmp(argv[0], "y"))
		fprintf(stderr, "%s:%d: %s\n",
			current_file->name, yylineno, argv[1]);

	return xstrdup("");
}