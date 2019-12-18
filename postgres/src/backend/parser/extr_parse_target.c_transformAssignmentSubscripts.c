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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COERCE_IMPLICIT_CAST ; 
 int /*<<< orphan*/  COERCION_ASSIGNMENT ; 
 int /*<<< orphan*/  ERRCODE_CANNOT_COERCE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * coerce_to_target_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_typcollation (scalar_t__) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * transformAssignmentIndirection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ transformContainerSubscripts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ transformContainerType (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
transformAssignmentSubscripts(ParseState *pstate,
							  Node *basenode,
							  const char *targetName,
							  Oid targetTypeId,
							  int32 targetTypMod,
							  Oid targetCollation,
							  List *subscripts,
							  bool isSlice,
							  List *indirection,
							  ListCell *next_indirection,
							  Node *rhs,
							  int location)
{
	Node	   *result;
	Oid			containerType;
	int32		containerTypMod;
	Oid			elementTypeId;
	Oid			typeNeeded;
	Oid			collationNeeded;

	Assert(subscripts != NIL);

	/* Identify the actual array type and element type involved */
	containerType = targetTypeId;
	containerTypMod = targetTypMod;
	elementTypeId = transformContainerType(&containerType, &containerTypMod);

	/* Identify type that RHS must provide */
	typeNeeded = isSlice ? containerType : elementTypeId;

	/*
	 * container normally has same collation as elements, but there's an
	 * exception: we might be subscripting a domain over a container type. In
	 * that case use collation of the base type.
	 */
	if (containerType == targetTypeId)
		collationNeeded = targetCollation;
	else
		collationNeeded = get_typcollation(containerType);

	/* recurse to create appropriate RHS for container assign */
	rhs = transformAssignmentIndirection(pstate,
										 NULL,
										 targetName,
										 true,
										 typeNeeded,
										 containerTypMod,
										 collationNeeded,
										 indirection,
										 next_indirection,
										 rhs,
										 location);

	/* process subscripts */
	result = (Node *) transformContainerSubscripts(pstate,
												   basenode,
												   containerType,
												   elementTypeId,
												   containerTypMod,
												   subscripts,
												   rhs);

	/* If target was a domain over container, need to coerce up to the domain */
	if (containerType != targetTypeId)
	{
		Oid			resulttype = exprType(result);

		result = coerce_to_target_type(pstate,
									   result, resulttype,
									   targetTypeId, targetTypMod,
									   COERCION_ASSIGNMENT,
									   COERCE_IMPLICIT_CAST,
									   -1);
		/* can fail if we had int2vector/oidvector, but not for true domains */
		if (result == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_CANNOT_COERCE),
					 errmsg("cannot cast type %s to %s",
							format_type_be(resulttype),
							format_type_be(targetTypeId)),
					 parser_errposition(pstate, location)));
	}

	return result;
}