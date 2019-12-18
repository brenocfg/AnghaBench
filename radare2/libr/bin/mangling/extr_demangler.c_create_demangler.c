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
struct TYPE_3__ {scalar_t__ symbol; scalar_t__ demangle; } ;
typedef  TYPE_1__ SDemangler ;
typedef  int /*<<< orphan*/  EDemanglerErr ;

/* Variables and functions */
 int /*<<< orphan*/  eDemanglerErrMemoryAllocation ; 
 int /*<<< orphan*/  eDemanglerErrOK ; 
 scalar_t__ malloc (int) ; 

EDemanglerErr create_demangler(SDemangler **demangler)
{
	EDemanglerErr err = eDemanglerErrOK;

	*demangler = (SDemangler *) malloc(sizeof(SDemangler));

	if (!*demangler) {
		err = eDemanglerErrMemoryAllocation;
		goto create_demagler_err;
	}

	(*demangler)->demangle = 0;
	(*demangler)->symbol = 0;

create_demagler_err:
	return err;
}