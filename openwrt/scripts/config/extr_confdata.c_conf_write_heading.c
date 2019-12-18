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
struct conf_printer {int /*<<< orphan*/  (* print_comment ) (int /*<<< orphan*/ *,char*,void*) ;} ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_1__* prompt; } ;
struct TYPE_3__ {char* text; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_2__ rootmenu ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,void*) ; 

__attribute__((used)) static void
conf_write_heading(FILE *fp, struct conf_printer *printer, void *printer_arg)
{
	char buf[256];

	snprintf(buf, sizeof(buf),
	    "\n"
	    "Automatically generated file; DO NOT EDIT.\n"
	    "%s\n",
	    rootmenu.prompt->text);

	printer->print_comment(fp, buf, printer_arg);
}