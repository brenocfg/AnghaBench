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
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ OperatorLookup (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int*) ; 
 scalar_t__ OperatorShellMake (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ QualifiedNameGetCreationNamespace (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 scalar_t__ pg_namespace_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static Oid
get_other_operator(List *otherOp, Oid otherLeftTypeId, Oid otherRightTypeId,
				   const char *operatorName, Oid operatorNamespace,
				   Oid leftTypeId, Oid rightTypeId, bool isCommutator)
{
	Oid			other_oid;
	bool		otherDefined;
	char	   *otherName;
	Oid			otherNamespace;
	AclResult	aclresult;

	other_oid = OperatorLookup(otherOp,
							   otherLeftTypeId,
							   otherRightTypeId,
							   &otherDefined);

	if (OidIsValid(other_oid))
	{
		/* other op already in catalogs */
		return other_oid;
	}

	otherNamespace = QualifiedNameGetCreationNamespace(otherOp,
													   &otherName);

	if (strcmp(otherName, operatorName) == 0 &&
		otherNamespace == operatorNamespace &&
		otherLeftTypeId == leftTypeId &&
		otherRightTypeId == rightTypeId)
	{
		/*
		 * self-linkage to this operator; caller will fix later. Note that
		 * only self-linkage for commutation makes sense.
		 */
		if (!isCommutator)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("operator cannot be its own negator or sort operator")));
		return InvalidOid;
	}

	/* not in catalogs, different from operator, so make shell */

	aclresult = pg_namespace_aclcheck(otherNamespace, GetUserId(),
									  ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_SCHEMA,
					   get_namespace_name(otherNamespace));

	other_oid = OperatorShellMake(otherName,
								  otherNamespace,
								  otherLeftTypeId,
								  otherRightTypeId);
	return other_oid;
}