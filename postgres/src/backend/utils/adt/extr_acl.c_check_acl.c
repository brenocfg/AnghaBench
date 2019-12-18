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
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 scalar_t__ ACLITEMOID ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/  const*) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/  const*) ; 
 int ARR_NDIM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
check_acl(const Acl *acl)
{
	if (ARR_ELEMTYPE(acl) != ACLITEMOID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("ACL array contains wrong data type")));
	if (ARR_NDIM(acl) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("ACL arrays must be one-dimensional")));
	if (ARR_HASNULL(acl))
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("ACL arrays must not contain null values")));
}