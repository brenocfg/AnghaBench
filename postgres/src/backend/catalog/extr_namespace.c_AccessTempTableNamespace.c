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

/* Variables and functions */
 int /*<<< orphan*/  InitTempTableNamespace () ; 
 int /*<<< orphan*/  MyXactFlags ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XACT_FLAGS_ACCESSEDTEMPNAMESPACE ; 
 int /*<<< orphan*/  myTempNamespace ; 

__attribute__((used)) static void
AccessTempTableNamespace(bool force)
{
	/*
	 * Make note that this temporary namespace has been accessed in this
	 * transaction.
	 */
	MyXactFlags |= XACT_FLAGS_ACCESSEDTEMPNAMESPACE;

	/*
	 * If the caller attempting to access a temporary schema expects the
	 * creation of the namespace to be pending and should be enforced, then go
	 * through the creation.
	 */
	if (!force && OidIsValid(myTempNamespace))
		return;

	/*
	 * The temporary tablespace does not exist yet and is wanted, so
	 * initialize it.
	 */
	InitTempTableNamespace();
}