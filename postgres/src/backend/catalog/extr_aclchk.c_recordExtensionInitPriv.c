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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  binary_upgrade_record_init_privs ; 
 int /*<<< orphan*/  creating_extension ; 
 int /*<<< orphan*/  recordExtensionInitPrivWorker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
recordExtensionInitPriv(Oid objoid, Oid classoid, int objsubid, Acl *new_acl)
{
	/*
	 * Generally, we only record the initial privileges when an extension is
	 * being created, but because we don't actually use CREATE EXTENSION
	 * during binary upgrades with pg_upgrade, there is a variable to let us
	 * know that the GRANT and REVOKE statements being issued, while this
	 * variable is true, are for the initial privileges of the extension
	 * object and therefore we need to record them.
	 */
	if (!creating_extension && !binary_upgrade_record_init_privs)
		return;

	recordExtensionInitPrivWorker(objoid, classoid, objsubid, new_acl);
}