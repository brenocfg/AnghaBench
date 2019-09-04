#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dt_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  f; } ;
struct TYPE_3__ {TYPE_2__* file; } ;

/* Variables and functions */
 TYPE_2__* current_srcfile ; 
 int /*<<< orphan*/  die (char*) ; 
 struct dt_info* parser_output ; 
 int /*<<< orphan*/  srcfile_push (char const*) ; 
 int treesource_error ; 
 int /*<<< orphan*/  yyin ; 
 TYPE_1__ yylloc ; 
 scalar_t__ yyparse () ; 

struct dt_info *dt_from_source(const char *fname)
{
	parser_output = NULL;
	treesource_error = false;

	srcfile_push(fname);
	yyin = current_srcfile->f;
	yylloc.file = current_srcfile;

	if (yyparse() != 0)
		die("Unable to parse input tree\n");

	if (treesource_error)
		die("Syntax error parsing input tree\n");

	return parser_output;
}