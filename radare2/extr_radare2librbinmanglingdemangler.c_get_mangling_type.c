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
typedef  int /*<<< orphan*/  EManglingType ;

/* Variables and functions */
 int /*<<< orphan*/  eManglingMicrosoft ; 
 int /*<<< orphan*/  eManglingUnknown ; 
 int /*<<< orphan*/  eManglingUnsupported ; 

__attribute__((used)) static EManglingType get_mangling_type(char *sym)
{
	EManglingType mangling_type = eManglingUnsupported;
	if (sym == 0) {
		mangling_type = eManglingUnknown;
		goto get_mangling_type_err;
	}

	switch (*sym) {
	case '?':
		mangling_type = eManglingMicrosoft;
		break;
	default:
		break;
	}

get_mangling_type_err:
	return mangling_type;
}