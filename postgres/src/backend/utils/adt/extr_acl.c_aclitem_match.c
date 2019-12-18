#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ai_grantee; scalar_t__ ai_grantor; } ;
typedef  TYPE_1__ AclItem ;

/* Variables and functions */

__attribute__((used)) static bool
aclitem_match(const AclItem *a1, const AclItem *a2)
{
	return a1->ai_grantee == a2->ai_grantee &&
		a1->ai_grantor == a2->ai_grantor;
}