#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ndim; int /*<<< orphan*/  elemtype; scalar_t__ dataoffset; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACLITEMOID ; 
 int /*<<< orphan*/  ACL_N_SIZE (int) ; 
 int* ARR_DIMS (TYPE_1__*) ; 
 int* ARR_LBOUND (TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Acl *
allocacl(int n)
{
	Acl		   *new_acl;
	Size		size;

	if (n < 0)
		elog(ERROR, "invalid size: %d", n);
	size = ACL_N_SIZE(n);
	new_acl = (Acl *) palloc0(size);
	SET_VARSIZE(new_acl, size);
	new_acl->ndim = 1;
	new_acl->dataoffset = 0;	/* we never put in any nulls */
	new_acl->elemtype = ACLITEMOID;
	ARR_LBOUND(new_acl)[0] = 1;
	ARR_DIMS(new_acl)[0] = n;
	return new_acl;
}