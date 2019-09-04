#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* symbol; } ;
typedef  TYPE_4__ symbol_node_t ;
struct TYPE_7__ {TYPE_1__* finfo; } ;
struct TYPE_8__ {char* name; TYPE_2__ info; } ;
struct TYPE_6__ {int value; int mask; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
aic_print_reg_dump_entry(FILE *dfile, symbol_node_t *curnode)
{
	int num_tabs;

	if (dfile == NULL)
		return;

	fprintf(dfile,
"	{ \"%s\",",
		curnode->symbol->name);

	num_tabs = 3 - (strlen(curnode->symbol->name) + 5) / 8;

	while (num_tabs-- > 0)
		fputc('\t', dfile);
	fprintf(dfile, "0x%02x, 0x%02x }",
		curnode->symbol->info.finfo->value,
		curnode->symbol->info.finfo->mask);
}