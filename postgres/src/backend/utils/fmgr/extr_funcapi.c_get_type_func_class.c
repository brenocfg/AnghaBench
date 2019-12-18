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
typedef  int /*<<< orphan*/  TypeFuncClass ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CSTRINGOID ; 
 int /*<<< orphan*/  RECORDOID ; 
 int /*<<< orphan*/  TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  TYPEFUNC_COMPOSITE_DOMAIN ; 
 int /*<<< orphan*/  TYPEFUNC_OTHER ; 
 int /*<<< orphan*/  TYPEFUNC_RECORD ; 
 int /*<<< orphan*/  TYPEFUNC_SCALAR ; 
#define  TYPTYPE_BASE 133 
#define  TYPTYPE_COMPOSITE 132 
#define  TYPTYPE_DOMAIN 131 
#define  TYPTYPE_ENUM 130 
#define  TYPTYPE_PSEUDO 129 
#define  TYPTYPE_RANGE 128 
 int /*<<< orphan*/  VOIDOID ; 
 int /*<<< orphan*/  getBaseType (int /*<<< orphan*/ ) ; 
 int const get_typtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TypeFuncClass
get_type_func_class(Oid typid, Oid *base_typeid)
{
	*base_typeid = typid;

	switch (get_typtype(typid))
	{
		case TYPTYPE_COMPOSITE:
			return TYPEFUNC_COMPOSITE;
		case TYPTYPE_BASE:
		case TYPTYPE_ENUM:
		case TYPTYPE_RANGE:
			return TYPEFUNC_SCALAR;
		case TYPTYPE_DOMAIN:
			*base_typeid = typid = getBaseType(typid);
			if (get_typtype(typid) == TYPTYPE_COMPOSITE)
				return TYPEFUNC_COMPOSITE_DOMAIN;
			else				/* domain base type can't be a pseudotype */
				return TYPEFUNC_SCALAR;
		case TYPTYPE_PSEUDO:
			if (typid == RECORDOID)
				return TYPEFUNC_RECORD;

			/*
			 * We treat VOID and CSTRING as legitimate scalar datatypes,
			 * mostly for the convenience of the JDBC driver (which wants to
			 * be able to do "SELECT * FROM foo()" for all legitimately
			 * user-callable functions).
			 */
			if (typid == VOIDOID || typid == CSTRINGOID)
				return TYPEFUNC_SCALAR;
			return TYPEFUNC_OTHER;
	}
	/* shouldn't get here, probably */
	return TYPEFUNC_OTHER;
}