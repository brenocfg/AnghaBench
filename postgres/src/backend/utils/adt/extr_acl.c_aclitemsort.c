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
typedef  int /*<<< orphan*/  AclItem ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_DAT (int /*<<< orphan*/ *) ; 
 int ACL_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aclitemComparator ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
aclitemsort(Acl *acl)
{
	if (acl != NULL && ACL_NUM(acl) > 1)
		qsort(ACL_DAT(acl), ACL_NUM(acl), sizeof(AclItem), aclitemComparator);
}