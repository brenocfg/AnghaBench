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
struct symbol {int type; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CONFIG_ ; 
#define  S_BOOLEAN 132 
#define  S_HEX 131 
#define  S_INT 130 
#define  S_STRING 129 
#define  S_TRISTATE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char const*,...) ; 

__attribute__((used)) static void
header_print_symbol(FILE *fp, struct symbol *sym, const char *value, void *arg)
{

	switch (sym->type) {
	case S_BOOLEAN:
	case S_TRISTATE: {
		const char *suffix = "";

		switch (*value) {
		case 'n':
			break;
		case 'm':
			suffix = "_MODULE";
			/* fall through */
		default:
			fprintf(fp, "#define %s%s%s 1\n",
			    CONFIG_, sym->name, suffix);
		}
		break;
	}
	case S_HEX: {
		const char *prefix = "";

		if (value[0] != '0' || (value[1] != 'x' && value[1] != 'X'))
			prefix = "0x";
		fprintf(fp, "#define %s%s %s%s\n",
		    CONFIG_, sym->name, prefix, value);
		break;
	}
	case S_STRING:
	case S_INT:
		fprintf(fp, "#define %s%s %s\n",
		    CONFIG_, sym->name, value);
		break;
	default:
		break;
	}

}