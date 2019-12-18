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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ RECORDOID ; 
#define  TYPTYPE_COMPOSITE 129 
#define  TYPTYPE_DOMAIN 128 
 scalar_t__ getBaseType (scalar_t__) ; 
 int const get_typtype (scalar_t__) ; 

bool
type_is_rowtype(Oid typid)
{
	if (typid == RECORDOID)
		return true;			/* easy case */
	switch (get_typtype(typid))
	{
		case TYPTYPE_COMPOSITE:
			return true;
		case TYPTYPE_DOMAIN:
			if (get_typtype(getBaseType(typid)) == TYPTYPE_COMPOSITE)
				return true;
			break;
		default:
			break;
	}
	return false;
}