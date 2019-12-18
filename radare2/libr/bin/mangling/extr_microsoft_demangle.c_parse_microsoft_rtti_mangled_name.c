#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type_str; } ;
typedef  TYPE_1__ STypeCodeStr ;
typedef  int /*<<< orphan*/  EDemanglerErr ;

/* Variables and functions */
 int /*<<< orphan*/  eDemanglerErrOK ; 
 int /*<<< orphan*/  eDemanglerErrUncorrectMangledSymbol ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int get_namespace_and_name (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_type_code_str_struct (TYPE_1__*) ; 
 char* r_str_newf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static EDemanglerErr parse_microsoft_rtti_mangled_name(char *sym, char **demangled_name) {
	EDemanglerErr err = eDemanglerErrOK;
	char *type = NULL;
	if (!strncmp (sym, "AT", 2)) {
		type = "union";
	} else if (!strncmp (sym, "AU", 2)) {
		type = "struct";
	} else if (!strncmp (sym, "AV", 2)) {
		type = "class";
	} else if (!strncmp (sym, "AW", 2)) {
		type = "enum";
	} else {
		err = eDemanglerErrUncorrectMangledSymbol;
		goto parse_microsoft_rtti_mangled_name_err;
	}
	STypeCodeStr type_code_str;
	init_type_code_str_struct (&type_code_str);
	int len = get_namespace_and_name (sym + 2, &type_code_str, NULL);
	if (!len) {
		err = eDemanglerErrUncorrectMangledSymbol;
		goto parse_microsoft_rtti_mangled_name_err;
	}

	*demangled_name = r_str_newf ("%s %s", type, type_code_str.type_str);
	free (type_code_str.type_str);

parse_microsoft_rtti_mangled_name_err:
	return err;
}