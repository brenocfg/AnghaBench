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
typedef  void* Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertState (int) ; 
 void* CurrentUserId ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 void* OuterUserId ; 
 scalar_t__ SecurityRestrictionContext ; 

__attribute__((used)) static void
SetOuterUserId(Oid userid)
{
	AssertState(SecurityRestrictionContext == 0);
	AssertArg(OidIsValid(userid));
	OuterUserId = userid;

	/* We force the effective user ID to match, too */
	CurrentUserId = userid;
}