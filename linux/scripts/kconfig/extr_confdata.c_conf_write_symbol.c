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
struct symbol {int type; } ;
struct conf_printer {int /*<<< orphan*/  (* print_symbol ) (int /*<<< orphan*/ *,struct symbol*,char const*,void*) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  S_STRING 129 
#define  S_UNKNOWN 128 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct symbol*,char const*,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct symbol*,char const*,void*) ; 
 char* sym_escape_string_value (char const*) ; 
 char* sym_get_string_value (struct symbol*) ; 

__attribute__((used)) static void conf_write_symbol(FILE *fp, struct symbol *sym,
			      struct conf_printer *printer, void *printer_arg)
{
	const char *str;

	switch (sym->type) {
	case S_UNKNOWN:
		break;
	case S_STRING:
		str = sym_get_string_value(sym);
		str = sym_escape_string_value(str);
		printer->print_symbol(fp, sym, str, printer_arg);
		free((void *)str);
		break;
	default:
		str = sym_get_string_value(sym);
		printer->print_symbol(fp, sym, str, printer_arg);
	}
}