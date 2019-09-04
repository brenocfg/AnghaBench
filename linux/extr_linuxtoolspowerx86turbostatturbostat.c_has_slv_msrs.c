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

/* Variables and functions */
#define  INTEL_FAM6_ATOM_MERRIFIELD 130 
#define  INTEL_FAM6_ATOM_MOOREFIELD 129 
#define  INTEL_FAM6_ATOM_SILVERMONT1 128 
 int /*<<< orphan*/  genuine_intel ; 

int has_slv_msrs(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return 0;

	switch (model) {
	case INTEL_FAM6_ATOM_SILVERMONT1:
	case INTEL_FAM6_ATOM_MERRIFIELD:
	case INTEL_FAM6_ATOM_MOOREFIELD:
		return 1;
	}
	return 0;
}