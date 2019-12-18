#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ai_grantee; scalar_t__ ai_grantor; scalar_t__ ai_privs; } ;
typedef  TYPE_1__ AclItem ;

/* Variables and functions */

__attribute__((used)) static int
aclitemComparator(const void *arg1, const void *arg2)
{
	const AclItem *a1 = (const AclItem *) arg1;
	const AclItem *a2 = (const AclItem *) arg2;

	if (a1->ai_grantee > a2->ai_grantee)
		return 1;
	if (a1->ai_grantee < a2->ai_grantee)
		return -1;
	if (a1->ai_grantor > a2->ai_grantor)
		return 1;
	if (a1->ai_grantor < a2->ai_grantor)
		return -1;
	if (a1->ai_privs > a2->ai_privs)
		return 1;
	if (a1->ai_privs < a2->ai_privs)
		return -1;
	return 0;
}