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
typedef  int /*<<< orphan*/  demangle_func ;
struct TYPE_3__ {int /*<<< orphan*/  demangle; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ SDemangler ;
typedef  int EManglingType ;
typedef  scalar_t__ EDemanglerErr ;

/* Variables and functions */
 scalar_t__ eDemanglerErrMemoryAllocation ; 
 scalar_t__ eDemanglerErrOK ; 
 scalar_t__ eDemanglerErrUnkown ; 
 scalar_t__ eDemanglerErrUnsupportedMangling ; 
#define  eManglingUnknown 129 
#define  eManglingUnsupported 128 
 int get_mangling_type (char*) ; 
 int /*<<< orphan*/  microsoft_demangle ; 
 int /*<<< orphan*/  strdup (char*) ; 

EDemanglerErr init_demangler(SDemangler *demangler, char *sym)
{
	EManglingType mangling_type = eManglingUnsupported;
	EDemanglerErr err = eDemanglerErrOK;

	// !!! sequence in this array need to be same as in EManglingType enum !!!
	demangle_func demangle_funcs[] = {
		microsoft_demangle,	// Microsoft demangling function
		0,					// Unsupported demangling
		0					// Unknown demangling
	};

	if (demangler == 0) {
		err =  eDemanglerErrMemoryAllocation;
		goto init_demangler_err;
	}

	mangling_type = get_mangling_type(sym);
	switch (mangling_type) {
	case eManglingUnsupported:
		err = eDemanglerErrUnsupportedMangling;
		break;
	case eManglingUnknown:
		err = eDemanglerErrUnkown;
		break;
	default:
		break;
	}

	if (err != eDemanglerErrOK) {
		goto init_demangler_err;
	}

	demangler->symbol = strdup(sym);
	demangler->demangle = demangle_funcs[mangling_type];

init_demangler_err:
	return err;
}