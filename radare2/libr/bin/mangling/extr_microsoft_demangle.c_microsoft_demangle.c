#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ symbol; } ;
typedef  TYPE_1__ SDemangler ;
typedef  int /*<<< orphan*/  EDemanglerErr ;

/* Variables and functions */
 int /*<<< orphan*/  abbr_names ; 
 int /*<<< orphan*/  abbr_types ; 
 int /*<<< orphan*/  eDemanglerErrMemoryAllocation ; 
 int /*<<< orphan*/  eDemanglerErrOK ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  parse_microsoft_mangled_name (scalar_t__,char**) ; 
 int /*<<< orphan*/  parse_microsoft_rtti_mangled_name (scalar_t__,char**) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_newf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 

EDemanglerErr microsoft_demangle(SDemangler *demangler, char **demangled_name) {
	EDemanglerErr err = eDemanglerErrOK;
//	RListIter *it = NULL;
//	char *tmp = NULL;

	// TODO: need refactor... maybe remove the static variable somewhere?
	abbr_types = r_list_newf (free);
	abbr_names = r_list_newf (free);

	if (!demangler || !demangled_name) {
		err = eDemanglerErrMemoryAllocation;
		goto microsoft_demangle_err;
	}
	
	if (!strncmp (demangler->symbol, ".?", 2)) {
		err = parse_microsoft_rtti_mangled_name (demangler->symbol + 2, demangled_name);
	} else {
		err = parse_microsoft_mangled_name (demangler->symbol + 1, demangled_name);
	}

microsoft_demangle_err:
	r_list_free (abbr_names);
	r_list_free (abbr_types);
	return err;
}