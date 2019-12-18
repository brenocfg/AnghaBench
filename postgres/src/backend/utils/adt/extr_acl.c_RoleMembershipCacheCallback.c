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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 void* InvalidOid ; 
 void* cached_member_role ; 
 void* cached_privs_role ; 

__attribute__((used)) static void
RoleMembershipCacheCallback(Datum arg, int cacheid, uint32 hashvalue)
{
	/* Force membership caches to be recomputed on next use */
	cached_privs_role = InvalidOid;
	cached_member_role = InvalidOid;
}